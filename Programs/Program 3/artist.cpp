/*
File       : artist.cpp
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

void ArtistIndex::addArtist(std::string myArtist, int myKey)
{
    bool foundArtist = false;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->artist == myArtist)
        {
            foundArtist = true;
            wp->up->pos = wp->up->pos + 1;
            Node * holdUp = wp->up;
            while(holdUp->up != NULL)
            {
                holdUp = holdUp->up;
            } // end while
            Node * p = new Node("~",myKey);
            p->down = holdUp->down;
            p->up = holdUp;
            holdUp->down->up=p;
            holdUp->down=p;
            break;
        }
        wp = wp->next;
    } // end while
    if(!foundArtist)
    {
        Node * hold = new Node(myArtist, myKey);
        hold->next = NULL;
        hold->prev = tail;
        tail->next = hold;
        tail = hold;
        size += 1;
        hold->up = new Node("numOfKeys", 1);
        hold->up->up = new Node("~", myKey);
        hold->up->up->down =  hold->up;
    } // end else
}

void ArtistIndex::getAllArtists()
{
    Node * wp = head->next;

    std::cout << size << std::endl;
    while(wp != NULL)
    {
        if(wp->up != NULL)
        {
            Node * holdUp = wp->up;
            int i = 0;
            std::vector<int> myVector;
            while(holdUp->up != NULL)
            {
                myVector.insert(myVector.begin() + i, holdUp->pos);
                holdUp = holdUp->up;
                ++i;
            } // end while

            std::string buildLine = "";
            for(i = 0; i < myVector.size(); ++i)
            {
                std::stringstream strs;
                strs << myVector.at(i);
                std::string temp_str = strs.str();

               buildLine += temp_str + " ";
            }
             std::cout << wp->artist << " " << buildLine << std::endl;
        }

        wp = wp->next;
    } //end while
}

void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist, int old_pos)
{
     int holdLocation = 0;

    //If new artist does not currently exist...
    if(!matchArtist(new_artist, holdLocation))
    {
       Node * wp = head->next;

        while(wp != NULL)
        {
            if(wp->artist == old_artist)
            {
                wp->artist = new_artist;
                return;
            }
            wp = wp->next;
        } // end while
    } // end if
    else
    {
        //Copy positions to new location
        //Delete old artist
        Node * oldNode = head->next;
        Node * newNode = head->next;

        //Find old Node
        while(oldNode != NULL)
        {
            if(oldNode->artist == old_artist)
            {
                break;
            }
             oldNode = oldNode->next;
        } // end while

         //Update count
        oldNode->up->pos = oldNode->up->pos - 1;

        //Find new Node
        while(newNode != NULL)
        {
            if(newNode->artist == new_artist)
            {
                break;
            }
             newNode = newNode->next;
        } // end while

        //Update count
        newNode->up->pos = newNode->up->pos + 1;

        //Find old pos
         Node * oldUp = oldNode->up;
          while(oldUp != NULL)
            {
                if(oldUp->pos == old_pos)
                {
                    break;
                }
                 oldUp = oldUp->up;
            } // end while

             //Find empty up in newNode
         Node * newUp = newNode->up;
          while(newUp->up != NULL)
            {
                 newUp = newUp->up;
            } // end while

            //Transfer Ups

            //Add New Up
            Node * p = new Node("~",old_pos);
            p->down = newUp->down;
            p->up = newUp;
            newUp->down->up=p;
            newUp->down=p;

            //Delete Old Up
            Node * deleteNode = oldUp;
            oldUp->down = deleteNode->up;

            delete deleteNode;

    } // end else
} // end updateArtist

void ArtistIndex::readSecondary()
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

        Node * hold = head->next;
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
                Node * hold = new Node(artist_name, 0);
                hold->next = NULL;
                hold->prev = tail;
                tail->next = hold;
                tail = hold;
                hold->up = new Node("numOfKeys", 0);
                hold->up->up = new Node("~", 0);
                hold->up->up->down = hold->up;
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
            hold = hold->next;
        } // End eof while
        input.close();
    } // end if
}


//Write sequential file from array
void ArtistIndex::writeSecondary()
{
    std::ofstream fout("artist_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    Node * wp = head->next->next;

    //For each item in my_list
    while(wp != NULL)
    {
        //Default
        buildLine = " ";
        //Number of Keys
        std::stringstream strs;
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
        wp = wp->next;
    } //end while

    //Close file
    fout.close();
} // end writeSecondary

std::vector<int> ArtistIndex::findArtist(std::string inArtist)
{
   std::vector<int> myVector;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->artist == inArtist)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                Node * holdUp = wp->up;
                 int i = 0;

                while(holdUp->up != NULL)
                {
                    myVector.insert(myVector.begin() + i, holdUp->pos);
                    holdUp = holdUp->up;
                    ++i;
                } // end while
                break;
            } // end if
            else
                break;
        }
        wp = wp->next;
    } // end while

    return myVector;
}
bool ArtistIndex::matchArtist(std::string inArtist, int &pos)
{
    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->artist == inArtist)
        {
            pos = wp->up->pos;
            return true;
        }
        wp = wp->next;
    } // end while
    pos = 0;
    return false;
}

bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    Node * wp = head->next;
    Node * wsp, * hold;

    while(wp != tail)
    {
        if(inArtist == wp->artist)
        {
            if(wp->down != NULL)
            {
                wsp = wp->down;
                while(wsp->down != NULL)
                    wsp = wsp->down;
                while(wsp->up != NULL)
                {
                    // call binary file with pos to delete record
                    hold = wsp;
                    wsp = wsp->up;
                    delete hold;
                }
            }
            // call binary file with pos to delete record
            hold = wp;
            wp->next->prev = wp->prev;
            wp->prev->next = wp->next;
            delete hold;
            return true;
        }
        wp = wp->next;
    }
    return false;
}

void ArtistIndex::killList()
{
    Node * wp = head;
    Node * wsp = NULL;
    Node * hold;
    while(wp != NULL)
    {
        if(wp->down != NULL)
        {
            wsp = wp->down;
            while(wsp->down != NULL)
                wsp = wsp->down;
            while(wsp->up != NULL)
            {
                hold = wsp;
                wsp = wsp->up;
                delete hold;
            }
        }
        hold = wp;
        wp = wp->next;
        delete hold;
    }
    return;
}


