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

            std::cout << wp->artist << " " << wp->up->up->pos <<  " " << holdUp->pos << std::endl;
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
        std::cout << wp->artist << " " << wp->up->up->pos << std::endl;
        wp = wp->next;
    } //end while
}

void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist)
{

}
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

        Node * hold = head;
        while(!input.eof() && position != size)
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
                hold->up = new Node("NumOfKeys", numOfKeys);
            }
            //Get artist name
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                hold->artist = part;
            }
            //Set pos to keys in line
            Node * holdUp = hold->up->up;
           while(holdUp != NULL)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    holdUp->pos = atoi(part.c_str());
                    line.erase(0, pos + delimiter.length());
                    holdUp = holdUp->up;
                }
            }

            //position++
            position++;

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

int * ArtistIndex::findArtist(std::string inArtist)
{
    static int emptyArray[1];
    emptyArray[0] = 0;
    return emptyArray;
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


