/*
File       : artist.cpp
Program    : Program 1 - Static Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//Return artist for a given position
std::string ArtistIndex::get_artist(int pos) const
{
    return ArtistIndex::my_list[pos].artist;
}

//Search array of artist indexes for the given artist
//Resize array if necessary
//Add new artist index as appropriate
//Return nothing
void ArtistIndex::addArtist(std::string inArtist, int my_key)
{
    //location (i)
    int location = 0;

    matchArtist(inArtist, location);
    if(location > 0)
    {
        //Current number of possible duplicate keys
        int numOfKeys = ArtistIndex::my_list[location].pos[0];
        //Max number of keys is 10 (From 1 to 11)
        if((numOfKeys + 1) != 11)
        {
            //Add the key
            ArtistIndex::my_list[location].pos[++numOfKeys] = my_key;
            //Update zero record to current number of keys
            ArtistIndex::my_list[location].pos[0] = numOfKeys;
        } //end if
    } // end if
    else
    {
        //A duplicate year was not found
        if((ArtistIndex::count + 1) != 15)
        {
            //Set the next year position
            int next_artist = ++ArtistIndex::count;
            //Set the year
            ArtistIndex::my_list[next_artist].artist = inArtist;
            //Set the first key
            ArtistIndex::my_list[next_artist].pos[1] = my_key;
            //Set zero record to 1
            ArtistIndex::my_list[next_artist].pos[0] = 1;
        }
    } // end else
} // end addArtist

//Search array of artist indexes for the given artist
//Default the artist for deletion and set dead flag
//Return found or not
bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    //Check for artist
    bool foundArtist = false;
    //For each item in my_list
    int location;
    if(matchArtist(inArtist, location))
    {
        //Found Artist
        foundArtist = true;
        //for each item in pos
        for(int k = 1; k < 11; ++k)
        {
            if(ArtistIndex::my_list[location].pos[k] == pos)
            {
                ArtistIndex::my_list[location].pos[k] = 0;
                --ArtistIndex::my_list[location].pos[0];
                if(ArtistIndex::my_list[location].pos[0] == 0)
                {
                    ArtistIndex::my_list[location].artist = "0";
                }
            } //end if
        } // end for
    } // end if
    return foundArtist;
} // end deleteArtist

//Search array of artist indexes for the given artist
//Update the old artist index with a new artist appropriately
//Return nothing
void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist)
{
    int new_location = 0;
    int old_location = 0;

    //If new artist does not currently exist...
    if(!matchArtist(new_artist, new_location))
    {
        if(matchArtist(old_artist, old_location))
        {
            //Change year
            my_list[old_location].artist = new_artist;
        } // end if
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
} // end updateArtist

//Search array of artist indexes for the given artist
//Set location to location in array
//Return found or not
bool ArtistIndex::matchArtist(std::string inArtist, int& location)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(ArtistIndex::my_list[i].artist == inArtist)
        {
            //Not conventional position in binary
            //but location in the list
            location = i;
            return true;
        } // end if
    } // end for

    return false;
} // end matchArtist

//Search array of artist indexes for the given artist
//Return int array of keys if found
//Return an empty int array if not found
int * ArtistIndex::findArtist(std::string inArtist)
{
    int location;
    //Empty array to return if artist not found
    static int emptyArray[1];
    emptyArray[0] = 0;

    if(matchArtist(inArtist, location))
        return ArtistIndex::my_list[location].pos;
    return emptyArray;
} // End findArtist

//Read sequential file and populate array
void ArtistIndex::readSecondary()
{
    std::ifstream input("my_artist_index.txt");
    std::string line;
    getline (input,line);
    count = atoi(line.c_str());

    for(int hold = 0; hold < 15; ++hold)
    {
        my_list[hold].artist = "****";
        for(int k = 0; k < 11; ++k)
            my_list[hold].pos[k] = 0;
    }

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
        input.close();
    } // end if
} // end readSecondary

//Write sequential file from array
void ArtistIndex::writeSecondary()
{
    std::ofstream fout("my_artist_index.txt");
    int my_count = 0;
    for(int i = 1; i < 15; ++i)
    {
        if(my_list[i].pos[0] != 0)
        {
            ++my_count;
        }
    }
    fout << my_count << std::endl;

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
        if(my_list[i].pos[0] != 0)
        {
            //Write to file
            fout << numOfKeys
                 << ArtistIndex::my_list[i].artist
                 << buildLine
                 << std::endl;
        } // end if
    } //end for

    //Close file
    fout.close();
} // end writeSecondary

