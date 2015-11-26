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
void ArtistIndex::addArtist(std::string Y, int P)
{
    if (root == NULL)
    {
        root = new Node(Y, P);
        root->up = new Node("numOfKeys", 1);
        root->up->up = new Node("~", P);
        root->up->up->down = root->up;
        ++size;
        return;
    } // end if
    else
    {
        addArtist(root, Y, P);
    } // end else
} // end addArtist

void ArtistIndex::addArtist(Node *& r, std::string my_Artist, int my_key)
{
    if (my_Artist == r->artist)
    {
        r->up->pos = r->up->pos + 1;
        Node * holdUp = r->up;
        while(holdUp->up != NULL)
        {
            holdUp = holdUp->up;
        } // end while
        Node * p = new Node("~",my_key);
        p->down = holdUp->down;
        p->up = holdUp;
        holdUp->down->up=p;
        holdUp->down=p;
    }
    else if (my_Artist < r->artist)
    {
        if (r->left == NULL)
        {
            r->left = new Node(my_Artist, my_key);
            r->left->up = new Node("numOfKeys", 1);
            r->left->up->up = new Node("~", my_key);
            r->left->up->up->down = r->left->up;
            ++size;
            return;
        }
        else
            return addArtist(r->left, my_Artist, my_key);
    }
    else if (my_Artist > r->artist)
    {
        if (r->right == NULL)
        {
            r->right = new Node(my_Artist, my_key);
            r->right->up = new Node("numOfKeys", 1);
            r->right->up->up = new Node("~", my_key);
            r->right->up->up->down = r->right->up;
            ++size;
            return;
        }
        else
            return addArtist(r->right, my_Artist, my_key);
    }
} // end addArtist using Node

//Display all artists
void ArtistIndex::getAllArtists()
{
    pushNodes();
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        std::cout << nodes[i]->artist << " " << nodes[i]->up->pos << std::endl;
    }
} // end getAllArtists

//Push nodes into the vector array
void ArtistIndex::pushNodes()
{
    nodes.clear();
    pushNode(root);
} // end pushNodes

//Push a node into the vector array
void ArtistIndex::pushNode(Node* r)
{
    if(r != NULL)
    {
        if(r->left != NULL)
            pushNode(r->left);
        nodes.push_back(r);
        if(r->right != NULL)
            pushNode(r->right);
    }
} // end pushNode


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

        Node * newNode = findArtistNode(root, new_artist, holdLocation);

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
    //Push nodes in the vector array
    pushNodes();
    std::ofstream fout("artist_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    //For each item in Linked List
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        Node * wp = nodes[i];
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
    } //end for

    //Close file
    fout.close();
} // end writeSecondary

//Find an artist and return an array of positions
std::vector<int> ArtistIndex::findArtist(std::string inArtist)
{
    std::vector<int> myVector;
//Push nodes in the vector array
    pushNodes();
    for (int i = 0; i < (int)nodes.size(); ++i)
    {
        Node * wp = nodes[i];
        if(wp->artist == inArtist)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                Node * holdUp = wp->up;
                int j = 0;

                while(holdUp != NULL)
                {
                    myVector.insert(myVector.begin() + j, holdUp->pos);
                    holdUp = holdUp->up;
                    ++j;
                } // end while
                break;
            } // end if
            else
                break;
        } //end if
    } // end for

    return myVector;
} // end findArtist

//Match an artist
bool ArtistIndex::matchArtist(std::string inArtist, int &pos)
{
    return (findArtistNode(root, inArtist, pos) != NULL);
} // end matchArtist

//Find a artist and return its pos using Node
ArtistIndex::Node * ArtistIndex::findArtistNode(Node *& r, std::string A, int& P)
{
    if(r!=NULL)
    {
        if(A == r->artist)
        {
            P = r->pos;
            return r;
        }
        if(A < r->artist)
            return findArtistNode(r->left, A, P);
        else
            return findArtistNode(r->right, A, P);
    }
    else
        return NULL;
} //end findArtistNode

//Delete a artist by artist
bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    deleteArtistByArtist(root, inArtist, pos);
} // end deleteArtist

//Delete artist by artist recursively
ArtistIndex::Node* ArtistIndex::deleteArtistByArtist(Node*& r, std::string A, int pos)
{
    if(r == NULL)
        return r;
    else if(A < r->artist)
        r->left = deleteArtistByArtist(r->left, A, pos);
    else if(A > r->artist)
        r->right = deleteArtistByArtist(r->right, A, pos);
    else
    {
        //if no children
        if(r->left == NULL && r->right == NULL)
        {
            delete r;
            r = NULL;
            --size;
        }
        //if no left child
        else if(r->left == NULL)
        {
            Node *temp = r;
            r = r->right;
            delete temp;
            --size;
        }
        //if no right child
        else if(r->right == NULL)
        {
            Node *temp = r;
            r = r->left;
            delete temp;
            --size;
        }
        //if left child and right child
        else
        {
            Node *temp = findMinNode(r->right);
            r->artist = temp->artist;
            r->pos = temp->pos;
            r->right = deleteArtistByArtist(r->right, temp->artist, temp->pos);
        }
    } // end else
    return r;
} // end deleteArtistByArtist

//Get lowest node
ArtistIndex::Node* ArtistIndex::findMinNode(Node*& r)
{
    while(r->left != NULL)
        r = r->left;
    return r;
} // end findMinNode

void ArtistIndex::killTree()
{
    RealKillTree(root);
};
void ArtistIndex::RealKillTree(Node*& r)
{
    if(r == NULL) return;
    RealKillTree(r->left);
    RealKillTree(r->right);
    RealKillTreeMiddle(r->up);
    delete r;
    return;
}
void ArtistIndex::RealKillTreeMiddle(Node *&m)
{
    if(m == NULL) return;
    if(m->up != NULL)
        RealKillTreeMiddle(m->up);
    delete m;
    m = NULL;
    return;
}
