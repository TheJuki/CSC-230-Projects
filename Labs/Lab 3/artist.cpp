/*
File       : artist.cpp
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include <iostream>
#include <fstream>
#include <sstream>

void SecondaryIndex::set_artist_key(std::string my_artist, int my_key)
{
    //Check for artist
    bool foundArtist = false;
     //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        if(SecondaryIndex::my_list[i].artist.compare(my_artist) == 0)
        {
            //Found Artist
            foundArtist = true;
            //Current number of possible duplicate keys
            int numOfKeys = SecondaryIndex::my_list[i].pos[0];
            //Max number of keys is 10 (From 1 to 11)
            if((numOfKeys + 1) != 11)
            {
                //Add the key
                SecondaryIndex::my_list[i].pos[++numOfKeys] = my_key;
                //Update zero record to current number of keys
                SecondaryIndex::my_list[i].pos[0] = numOfKeys;
            } //end if
        } // end if
    } // end for

    //A duplicate artist was not found
    //Max number of artist indices is 14 (From 1 to 15)
    if(!foundArtist && ((SecondaryIndex::count + 1) != 15))
    {
        //Set the next artist possition
        int next_artist = ++SecondaryIndex::count;
        //Set the artist
        SecondaryIndex::my_list[next_artist].artist = my_artist;
        //Set the first key
        SecondaryIndex::my_list[next_artist].pos[1] = my_key;
        //Set zero record to 1
        SecondaryIndex::my_list[next_artist].pos[0] = 1;
    } //end if
} // end set_artist_key

void SecondaryIndex::updateArtist(std::string new_artist, int pos[])
{
    //Stub
}

void SecondaryIndex::writeSecondary()
{
    //Sequential file for Secondary indices
   std::ofstream outSecondary ("secondaryArtists.txt");

    //A normal string used as a string builder
    std::string buildLine;

    //For each item in my_list
     for(int i = 1; i < 15; ++i)
     {
         //Default
         buildLine = "";

         //for each item in pos
         for(int k = 1; k < 11; ++k)
         {
             if(SecondaryIndex::my_list[i].pos[k] != 0)
             {
                 //Convert the key to a string
                 std::stringstream strs;
                 strs << SecondaryIndex::my_list[i].pos[k];
                 std::string temp_str = strs.str();
                 //Add key to buildLine
                 buildLine += temp_str + ", ";
             } //end if
         } // end for

         //If there is at least 1 key then write to file
         if(SecondaryIndex::my_list[i].pos[0] != 0)
         {
             //Write to file
            outSecondary << buildLine
                         << SecondaryIndex::my_list[i].artist
                         << std::endl;
         } // end if
     } //end for

     //Close file
     outSecondary.close();

} // End writeSecondary

void SecondaryIndex::readSecondary()
{
    // Stub
}

bool SecondaryIndex::matchArtist(std::string inArtist, int pos[])
{
    return false;
}


