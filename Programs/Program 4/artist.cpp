/*
File       : artist.cpp
Program    : Program 4 - Binary Search Tree Indexes
Due Date   : December 4, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

//Add an artist (Sort Alphabetically)
void ArtistIndex::addArtist(std::string A, int P)
{
    if(root == NULL)
    {
         Node * wp = new Node(A, P);
         wp->right = NULL;
         wp->left = root;
         root = wp;
         size += 1;
         return;
    }

    bool foundArtist = false;

    Node * wp = root;

    while(wp != NULL)
    {
        if(wp->artist == A)
        {
            foundArtist = true;
            wp->up->pos = wp->up->pos + 1;
            Node * holdUp = wp->up;
            while(holdUp->up != NULL)
            {
                holdUp = holdUp->up;
            } // end while
            Node * p = new Node("~",P);
            p->down = holdUp->down;
            p->up = holdUp;
            holdUp->down->up=p;
            holdUp->down=p;
            break;
        }
        wp = wp->left;
    } // end while
    if(!foundArtist)
    {
        if(root->artist>A)
        {
            Node * wp = new Node(A, P);
            wp->right = NULL;
            wp->left = root;
            root->left = wp;
            root = wp;
            size += 1;

            root->up = new Node("numOfKeys", 1);
            root->up->up = new Node("~", P);
            root->up->up->down =  root->up;
        } // end if
        else
        {
            Node * wp = root->left;
            while(wp != NULL)
            {
                if(wp->artist>A)
                {
                    Node * wp2 = new Node(A,P);
                    wp2->right = wp->right;
                    wp2->left = wp;
                    wp->right->left=wp2;
                    wp->right=wp2;
                    size += 1;

                    wp->right->up = new Node("numOfKeys", 1);
                    wp->right->up->up = new Node("~", P);
                    wp->right->up->up->down =  wp->right->up;
                    return;
                } // end if
                wp=wp->left;
            } // end while
        } // end else
    } // end else
} // end addArtist

//Display all artists
void ArtistIndex::getAllArtists()
{
    Node * wp = root->left;

    std::cout << size << std::endl;
    while(wp != NULL)
    {
        if(wp->up != NULL)
        {
            Node * holdUp = wp->up;
            int i = 0;
            std::vector<int> myVector;
            while(holdUp != NULL)
            {
                myVector.insert(myVector.begin() + i, holdUp->pos);
                holdUp = holdUp->up;
                ++i;
            } // end while

            std::string buildLine = "";
            for(i = 0; i < (int)myVector.size(); ++i)
            {
                std::stringstream strs;
                strs << myVector.at(i);
                std::string temp_str = strs.str();

                buildLine += temp_str + " ";
            } // end for
            std::cout << wp->artist << " " << buildLine << std::endl;
        } // end if

        wp = wp->left;
    } //end while
} // end getAllArtists

//Update an artist
void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist, int old_pos)
{
     int holdLocation = 0;

    //If new artist does not currently exist...
    if(!matchArtist(new_artist, holdLocation))
    {
        addArtist(new_artist, old_pos);
    } // end if
    else
    {
        //Copy positions to new location

        Node * newNode = root->left;

        //Find new Node
        while(newNode != NULL)
        {
            if(newNode->artist == new_artist)
            {
                break;
            } // end if
            newNode = newNode->left;
        } // end while

        //Update count
        newNode->up->pos = newNode->up->pos + 1;

        //Find empty up in newNode
        Node * newUp = newNode->up;
        while(newUp->up != NULL)
        {
            newUp = newUp->up;
        } // end while

        //Add New Up
        Node * p = new Node("~",old_pos);
        p->down = newUp->down;
        p->up = newUp;
        newUp->down->up=p;
        newUp->down=p;

    } // end else
    //Delete Old Up
    deleteArtist(old_artist, old_pos);

} // end updateArtist

//Read in artists
void ArtistIndex::readFile()
{
    std::ifstream input("artist_index.txt");
    std::string line;
    getline (input,line);
    size = atoi(line.c_str());

    if (input.is_open())
    {
        //Set position to 1
        long position = 1;
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        size_t pos = 0;
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;
        //Number of keys in line
        int numOfKeys = 0;
        //Artist Name
        std::string artist_name = "";

        while(!input.eof() && position != (int)(size+1))
        {
            //Read in a line from the sequential file
            getline (input,line);

            //Defaults
            pos = 0;
            part = "";
            numOfKeys = 0;

            //Get Number of keys
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                numOfKeys = atoi(part.c_str());
            }

            //Get artist name
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                artist_name = part;
                line.erase(0, pos + delimiter.length());
                --size;
            }

            //Set pos to keys in line
            for(int i = 0; i < numOfKeys; ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    addArtist(artist_name, atoi(part.c_str()));
                    line.erase(0, pos + delimiter.length());
                }
            } // end for

            position++;
        } // End eof while
        input.close();
    } // end if
} // end readSecondary


//Write out artists
void ArtistIndex::writeFile()
{
    std::ofstream fout("artist_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    Node * wp = root->left;

    //For each item in Linked List
    while(wp != NULL)
    {
        //Default
        buildLine = " ";
        //Number of Keys
        std::stringstream strs;
        if(wp->up != NULL)
        {
            strs << wp->up->pos;
            std::string temp_str = strs.str();
            //Add number of keys to numOfKeys
            numOfKeys = temp_str + " ";

            Node * holdUp = wp->up->up;
            //for each item in pos
            while(holdUp != NULL)
            {
                if(holdUp->pos != 0)
                {
                    //Convert the key to a string
                    std::stringstream strs;
                    strs << holdUp->pos;
                    std::string temp_str = strs.str();
                    //Add key to buildLine
                    buildLine += temp_str + " ";
                } //end if
                holdUp = holdUp->up;
            } // end while

            //If there is at least 1 key then write to file
            if(wp->up->pos != 0)
            {
                //Write to file
                fout << numOfKeys
                     << wp->artist
                     << buildLine
                     << std::endl;
            } // end if
        } // end if
        wp = wp->left;
    } //end while

    //Close file
    fout.close();
} // end writeSecondary

//Find an artist and return an array of positions
std::vector<int> ArtistIndex::findArtist(std::string inArtist)
{
    std::vector<int> myVector;

    Node * wp = root->left;

    while(wp != NULL)
    {
        if(wp->artist == inArtist)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                Node * holdUp = wp->up;
                int i = 0;

                while(holdUp != NULL)
                {
                    myVector.insert(myVector.begin() + i, holdUp->pos);
                    holdUp = holdUp->up;
                    ++i;
                } // end while
                break;
            } // end if
            else
                break;
        } //end if
        wp = wp->left;
    } // end while

    return myVector;
} // end findArtist

//Match an artist
bool ArtistIndex::matchArtist(std::string inArtist, int &pos)
{
    Node * wp = root->left;

    while(wp != NULL)
    {
        if(wp->artist == inArtist)
        {
            pos = wp->up->pos;
            return true;
        } // end if
        wp = wp->left;
    } // end while
    pos = 0;
    return false;
} // end matchArtist

//Delete an artist
bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    Node * wp = root->left;
    Node * holdUp, * hold;

    while(wp != NULL)
    {
        if(inArtist == wp->artist)
        {
            if(wp->up != NULL)
            {
                holdUp = wp->up->up;
                while(holdUp != NULL)
                {
                    hold = holdUp;
                    holdUp = holdUp->up;
                    if(hold->pos == pos)
                    {
                        wp->up->pos = wp->up->pos - 1;
                        if(hold->down != NULL)
                            hold->down->up = hold->up;
                        if(hold->up != NULL)
                            hold->up->down = hold->down;
                        delete hold;
                    }
                } // end while
            } // end if
            if(wp->up->pos == 0)
            {
                hold = wp;
                wp->left->right = wp->right;
                wp->right->left = wp->left;
                delete hold;
                size--;
            }

            return true;
        } // end if
        wp = wp->left;
    } // end while
    return false;
} // end deleteArtist

void ArtistIndex::killTree()
{
    RealKillTree(root);
};
void ArtistIndex::RealKillTree(Node*& r)
{
    if(r == NULL) return;
    RealKillTree(r->left);
    RealKillTree(r->right);
    RealKillTreeMiddle(r->down);
    delete r;
    return;
}
void ArtistIndex::RealKillTreeMiddle(Node *&m)
{
    if(m == NULL) return;
    if(m->down != NULL)
        RealKillTreeMiddle(m->down);
    delete m;
    m = NULL;
    return;
}
