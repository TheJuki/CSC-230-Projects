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

std::string ArtistIndex::get_artist(int pos) const
{
    return ArtistIndex::my_list[pos].artist;
}

void ArtistIndex::set_artist_key(std::string my_artist, int my_key)
{
    //Check for artist
    bool foundArtist = false;
     //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        if(ArtistIndex::my_list[i].artist.compare(my_artist) == 0)
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
        ArtistIndex::my_list[next_artist].artist = my_artist;
        //Set the first key
        ArtistIndex::my_list[next_artist].pos[1] = my_key;
        //Set zero record to 1
        ArtistIndex::my_list[next_artist].pos[0] = 1;
    } //end if
} // end set_artist_key

void ArtistIndex::updateArtist(std::string new_artist, int pos[])
{
     for(int i = 1; i < 15; ++i)
    {
         if(ArtistIndex::my_list[i].pos == pos)
         {
             ArtistIndex::my_list[i].artist = new_artist;
             break;
         }
    }
}

void ArtistIndex::writeSecondary()
{
   //Sequential file for Secondary indices
   std::ofstream outSecondary ("secondaryArtists.txt");

    //A normal string used as a string builder
    std::string buildLine;

    //For each item in my_list
     for(int i = 1; i < 15; ++i)
     {
         //Default
         buildLine = my_list[i].pos[0] + ", ";

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
                 buildLine += temp_str + ", ";
             } //end if
         } // end for

         //If there is at least 1 key then write to file
         if(ArtistIndex::my_list[i].pos[0] != 0)
         {
             //Write to file
            outSecondary << buildLine
                         << ArtistIndex::my_list[i].artist
                         << std::endl;
         } // end if
     } //end for

     //Close file
     outSecondary.close();

} // End writeSecondary


void ArtistIndex::readSecondary()
{
    //Open Sequential file for reading using ifstream
    ifstream input;
    input.open ("ArtistIndexes.txt, fstream::in);

    if (input.is_open())
    {
        //Set position to 1
        long position = 1;
        //Create Secondary Index objects
        ArtistIndex artistInx;
        //delimiter is a space
        string delimiter = ", ";
        //size of string
        size_t pos = 0;
        //Part of line
        int partNumber = 1;
        //Line in file as a string
        string line;
        //string of part
        string part;

        //----------------------------------------//
        //Parts of binary object in line variables
        string my_artist;
        int positionInBinary = 0;

        //while(not sequential.eof())
        while(!input.eof())
        {
            //Read in a line from the sequential file
            getline (input,line);

            //cout << line;

            //Defaults
            my_artist =  "";
            positionInBinary = 0;

            pos = 0;
            partNumber = 1;
            part = "";

            //Find each part separated by the delimiter and
            //Set the respective variables
            //Ex. TITLE ARTIST TYPE YEAR PRICE COUNT
            while ((pos = line.find(delimiter)) != string::npos) {
                part = line.substr(0, pos);
                switch (partNumber)
                {
                case(1) : my_title = part;
                    break;
                case(2) : my_artist = part;
                    break;
                case(3) : my_type = part;
                    break;
                case(4) : my_year = std::atoi(part.c_str());
                    break;
                case(5) : my_price = std::atoi(part.c_str());
                    break;
                case(6) : my_count = std::atoi(part.c_str());
                    break;
                default: //None
                    break;
                } // end switch

                line.erase(0, pos + delimiter.length());
                partNumber++;
            } // end delimiter While

            //Convert line into binary file object named me
            MyClass me(my_title, my_artist, my_type,
               my_year, my_price, my_count);

            //Seek position and write record in binary file
            me.writeIt(outputFile, position);

            //Pass Primary Key information to Primary Index(title, position)
            primaryInx.set_title_key(my_title, position);

            //Pass Secondary Key information to Secondary Index(artist or year, position)
            artistInx.set_artist_key(my_artist, position);
            yearInx.set_year_key(my_year, position);

            //position++
            position++;

        } // End eof while

        //Close all files
        input.close();
}

bool ArtistIndex::matchArtist(std::string inArtist, int pos[])
{
    return false;
}


