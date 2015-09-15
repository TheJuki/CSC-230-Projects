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
    // Stub
}

void YearIndex::writeSecondary()
{
    //Sequential file for Secondary indices
   std::ofstream outSecondary ("secondaryYears.txt");

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
             if(YearIndex::my_list[i].pos[k] != 0)
             {
                 //Convert the key to a string
                 std::stringstream strs;
                 strs << YearIndex::my_list[i].pos[k];
                 std::string temp_str = strs.str();
                 //Add key to buildLine
                 buildLine += temp_str + ", ";
             } //end if
         } // end for

         //If there is at least 1 key then write to file
         if(YearIndex::my_list[i].pos[0] != 0)
         {
             //Write to file
            outSecondary << buildLine
                         << YearIndex::my_list[i].year
                         << std::endl;
         } // end if
     } //end for

     //Close file
     outSecondary.close();
}

void YearIndex::readSecondary()
{
    // Stub
}

void YearIndex::matchYear(int inYear, int pos[])
{
    // Stub
}


