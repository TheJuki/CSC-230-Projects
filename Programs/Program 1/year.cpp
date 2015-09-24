/*
File       : year.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Code for year data
*/

#include "year.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

int YearIndex::get_year(int pos) const
{
    return YearIndex::my_list[pos].year;
}

void YearIndex::set_year_key(int my_year, int my_key)
{
    //Check for year
    bool foundYear = false;
     //For each item in my_list
    for(int i = 1; i < 15; ++i)
    {
        if(YearIndex::my_list[i].year == my_year)
        {
            //Found Year
            foundYear = true;
            //Current number of possible duplicate keys
            int numOfKeys = YearIndex::my_list[i].pos[0];
            //Max number of keys is 10 (From 1 to 11)
            if((numOfKeys + 1) != 11)
            {
                //Add the key
                YearIndex::my_list[i].pos[++numOfKeys] = my_key;
                //Update zero record to current number of keys
                YearIndex::my_list[i].pos[0] = numOfKeys;
            } //end if
        } // end if
    } // end for

    //A duplicate year was not found
    //Max number of year indices is 14 (From 1 to 15)
    if(!foundYear && ((YearIndex::count + 1) != 15))
    {
        //Set the next year position
        int next_year = ++YearIndex::count;
        //Set the year
        YearIndex::my_list[next_year].year = my_year;
        //Set the first key
        YearIndex::my_list[next_year].pos[1] = my_key;
        //Set zero record to 1
        YearIndex::my_list[next_year].pos[0] = 1;
    } //end if
} // end YearIndex

void YearIndex::updateYear(int new_year, int pos[])
{
     for(int i = 1; i < 15; ++i)
    {
         if(YearIndex::my_list[i].pos == pos)
         {
             YearIndex::my_list[i].year = new_year;
             break;
         }
    }
}

bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    //Check for year
    bool foundYear = false;
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

void YearIndex::writeSecondary()
{
    //Sequential file for Secondary indices
   std::ofstream outSecondary ("secondaryYears.txt");

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
         strs << YearIndex::my_list[i].pos[0];
         std::string temp_str = strs.str();
         //Add number of keys to numOfKeys
         numOfKeys = temp_str + " ";

         //for each item in pos
         for(int k = 1; k < 11; ++k)
         {
             if(YearIndex::my_list[i].pos[k] != 0)
             {
                 //Convert the key to a string
                 std::stringstream strs;
                 strs << YearIndex::my_list[i].pos[k];
                 std::string temp_str = strs.str();
                 //Add key to buildLine
                 buildLine += temp_str + " ";
             } //end if
         } // end for

         //If there is at least 1 key then write to file
         if(YearIndex::my_list[i].pos[0] != 0)
         {
             //Write to file
            outSecondary << numOfKeys
                         << YearIndex::my_list[i].year
                         << buildLine
                         << std::endl;
         } // end if
     } //end for

     //Close file
     outSecondary.close();
}

void YearIndex::readSecondary()
{
     //Open Sequential file for reading using ifstream
    std::ifstream input;
    input.open ("secondaryYears.txt", std::fstream::in);

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
                 YearIndex::my_list[position].pos[0] = numOfKeys;
            }
            //Get year
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                 part = line.substr(0, pos);
                 line.erase(0, pos + delimiter.length());
                 YearIndex::my_list[position].year = atoi(part.c_str());
            }
            //Set pos to keys in line
            for(int i = 1; i < (numOfKeys + 1); ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                     part = line.substr(0, pos);
                     YearIndex::my_list[position].pos[i] = atoi(part.c_str());
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

bool YearIndex::matchYear(int inYear, int pos[])
{
    int location, count;

    for (location = 1; location <= YearIndex::my_list[0].pos[0]; ++location)
    {
        if(YearIndex::my_list[location].year == inYear)
        {
            for(count = 1; count <= YearIndex::my_list[location].pos[0]; ++count)
            {
                pos[count - 1] = YearIndex::my_list[location].pos[count];
            }
            return true;
        }
    }
    return false;
} // matchYear

int * YearIndex::findYear(int inYear)
{
    int location;
    //Empty array to return if artist not found
    static int emptyArray[1];
    emptyArray[0] = 0;

    for (location = 1; location <= YearIndex::my_list[0].pos[0]; ++location)
    {
        if(YearIndex::my_list[location].year == inYear)
        {
            return YearIndex::my_list[location].pos;
        }
    }
    return emptyArray;
} // End findYear



