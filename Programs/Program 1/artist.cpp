/*
File       : artist.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

std::string ArtistIndex::get_artist(int pos) const
{
    return ArtistIndex::my_list[pos].artist;
}

void ArtistIndex::set_artist_key(std::string inArtist, int my_key)
{
    //Check for artist
    bool foundArtist = false;
    //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        if(ArtistIndex::my_list[i].artist == inArtist)
        {
            //Found Artist
            foundArtist = true;
            //Current number of possible duplicate keys
            int numOfKeys = ArtistIndex::my_list[i].pos[0];
            //Max number of keys is 10 (From 1 to 11)
            if((numOfKeys + 1) != 11)
            {
                //Add the key
                ArtistIndex::my_list[i].pos[++numOfKeys] = my_key;
                //Update zero record to current number of keys
                ArtistIndex::my_list[i].pos[0] = numOfKeys;
            } //end if
        } // end if
    } // end for

    //A duplicate artist was not found
    //Max number of artist indices is 14 (From 1 to 15)
    if(!foundArtist && ((ArtistIndex::count + 1) != 15))
    {
        //Set the next artist position
        int next_artist = ++ArtistIndex::count;
        //Set the artist
        ArtistIndex::my_list[next_artist].artist = inArtist;
        //Set the first key
        ArtistIndex::my_list[next_artist].pos[1] = my_key;
        //Set zero record to 1
        ArtistIndex::my_list[next_artist].pos[0] = 1;
    } //end if
} // end set_artist_key

bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    //Check for artist
    bool foundArtist = false;
    //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        if(ArtistIndex::my_list[i].artist == (inArtist))
        {
            //Found Artist
            foundArtist = true;
            //for each item in pos
            for(int k = 1; k < 11; ++k)
            {
                if(ArtistIndex::my_list[i].pos[k] == pos)
                {
                    ArtistIndex::my_list[i].pos[k] = 0;
                    --ArtistIndex::my_list[i].pos[0];
                    if(ArtistIndex::my_list[i].pos[0] == 0)
                    {
                        ArtistIndex::my_list[i].artist = "0";
                    }
                } //end if
            } // end for
        } // end if
    } // end for
    return foundArtist;
}

void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist)
{
    int new_location = 0;
    int old_location = 0;

    if(!matchArtist(new_artist, new_location))
    {
        for(int i = 1; i < 15; ++i)
        {
            if(my_list[i].artist == old_artist)
            {
                //Change artist
                my_list[i].artist = new_artist;
                break;
            } // end if
        } // end for
    } // end if
    else
    {
        //Copy positions to new location
        //Delete old artist
        matchArtist(old_artist, old_location);
        for (int i = 1; i < 11; ++i)
        {
            for (int k = 1; k < 11; ++k)
            {
                if(my_list[old_location].pos[i] != 0 && my_list[new_location].pos[k] == 0)
                {
                    my_list[new_location].pos[k] = my_list[old_location].pos[i];
                    ++my_list[new_location].pos[0];
                    deleteArtist(old_artist, my_list[old_location].pos[i]);
                    break;
                } // end if
            } // end for k
        } // end for i
    } // end else

}

void ArtistIndex::writeSecondary()
{
    //Sequential file for Secondary indices
    std::ofstream outSecondary ("secondaryArtists.txt");

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        //Default
        buildLine = " ";

        //Number of Keys
        std::stringstream strs;
        strs << ArtistIndex::my_list[i].pos[0];
        std::string temp_str = strs.str();
        //Add number of keys to numOfKeys
        numOfKeys = temp_str + " ";

        //for each item in pos
        for(int k = 1; k < 11; ++k)
        {
            if(ArtistIndex::my_list[i].pos[k] != 0)
            {
                //Convert the key to a string
                std::stringstream strs;
                strs << ArtistIndex::my_list[i].pos[k];
                std::string temp_str = strs.str();
                //Add key to buildLine
                buildLine += temp_str + " ";
            } //end if
        } // end for

        //If there is at least 1 key then write to file
        if(ArtistIndex::my_list[i].pos[0] != 0)
        {
            //Write to file
            outSecondary << numOfKeys
                         << ArtistIndex::my_list[i].artist
                         << buildLine
                         << std::endl;
        } // end if
    } //end for

    //Close file
    outSecondary.close();

} // End writeSecondary


void ArtistIndex::readSecondary()
{
    //Open Sequential file for reading using ifstream
    std::ifstream input;
    input.open ("secondaryArtists.txt", std::fstream::in);

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

        //while(not sequential.eof())
        while(!input.eof() && position != 15)
        {
            //Read in a line from the sequential file
            getline (input,line);

            //cout << line;

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
                ArtistIndex::my_list[position].pos[0] = numOfKeys;
            }
            //Get artist name
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                ArtistIndex::my_list[position].artist = part;
            }
            //Set pos to keys in line
            for(int i = 1; i < (numOfKeys + 1); ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    ArtistIndex::my_list[position].pos[i] = atoi(part.c_str());
                    line.erase(0, pos + delimiter.length());
                }
            }

            //position++
            position++;

        } // End eof while

        //Set zero record to number of indexes
        if(position > 14)
            my_list[0].pos[0] = 14;
        else
            my_list[0].pos[0] = position;
        //Close all files
        count = my_list[0].pos[0];
        input.close();
    } // end if
} //end readSecondary

bool ArtistIndex::matchArtist(std::string inArtist, int& location)
{
    for (location = 1; location <= ArtistIndex::my_list[0].pos[0]; ++location)
    {
        if(my_list[location].artist == inArtist)
        {
            return true;
        }
    }
    return false;
} // matchArtist

int * ArtistIndex::findArtist(std::string inArtist)
{
    int location;
    //Empty array to return if artist not found
    static int emptyArray[1];
    emptyArray[0] = 0;

    for (location = 1; location <= ArtistIndex::my_list[0].pos[0]; ++location)
    {
        if(ArtistIndex::my_list[location].artist == inArtist)
        {
            return ArtistIndex::my_list[location].pos;
        }
    }
    return emptyArray;
} // End findArtist


