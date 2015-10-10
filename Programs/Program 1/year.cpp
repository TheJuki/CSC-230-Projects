/*
File       : year.cpp
Program    : Program 1 - Dynamic Array Based Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Code for year data
*/

#include "year.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

//Return year for a given position
int YearIndex::get_year(int pos) const
{
    return YearIndex::my_list[pos].year;
}

//Search array of year indexes for the given year
//Resize array if necessary
//Add new year index as appropriate
//Return nothing
void YearIndex::addYear(int my_year, int my_key)
{
    //location (i)
    int location = 0;

    matchYear(my_year, location);
    if(location > 0)
    {
        //Current number of possible duplicate keys
        int numOfKeys = YearIndex::my_list[location].pos[0];
        //Max number of keys is 10 (From 1 to 11)
        if((numOfKeys + 1) != 11)
        {
            //Add the key
            YearIndex::my_list[location].pos[++numOfKeys] = my_key;
            //Update zero record to current number of keys
            YearIndex::my_list[location].pos[0] = numOfKeys;
        } //end if
    } // end if
    else
    {
        //A duplicate year was not found
        if((YearIndex::count + 1) == YearIndex::capacity)
        {
            YearIndex::resize();
        }
        //Set the next year position
        int next_year = ++YearIndex::count;
        //Set the year
        YearIndex::my_list[next_year].year = my_year;
        //Set the first key
        YearIndex::my_list[next_year].pos[1] = my_key;
        //Set zero record to 1
        YearIndex::my_list[next_year].pos[0] = 1;
    } // end else
} // end addYear

//Search array of year indexes for the given year
//Update the old year index with a new year appropriately
//Return nothing
void YearIndex::updateYear(int old_year, int new_year)
{
    int new_location = 0;
    int old_location = 0;

    if(!matchYear(new_year, new_location))
    {
        if(matchYear(old_year, old_location))
        {
            //Change year
            my_list[old_location].year = new_year;
        } // end if
    } // end if
    else
    {
        //Copy positions to new location
        //Delete old year
        matchYear(old_year, old_location);
        for (int i = 1; i < 11; ++i)
        {
            for (int k = 1; k < 11; ++k)
            {
                if(my_list[old_location].pos[i] != 0 && my_list[new_location].pos[k] == 0)
                {
                    my_list[new_location].pos[k] = my_list[old_location].pos[i];
                    ++my_list[new_location].pos[0];
                    deleteYear(old_year, my_list[old_location].pos[i]);
                    break;
                } // end if
            } // end for k
        } // end for i
    } // end else
} // end updateYear

//Search array of year indexes for the given year
//Default the year for deletion and set dead flag
//Return found or not
bool YearIndex::deleteYear(int inYear, int pos)
{
    //Check for year
    bool foundYear = false;
    //For each item in my_list
    int location;
    if(matchYear(inYear, location))
    {
        //Found Year
        foundYear = true;
        //for each item in pos
        for(int k = 1; k < 11; ++k)
        {
            if(YearIndex::my_list[location].pos[k] == pos)
            {
                YearIndex::my_list[location].pos[k] = 0;
                --YearIndex::my_list[location].pos[0];
                if(YearIndex::my_list[location].pos[0] == 0)
                {
                    YearIndex::my_list[location].year = 0;
                }
            } //end if
        } // end for
    } // end if

    return foundYear;
} // end deleteYear

//Search array of year indexes for the given year
//Set location to location in array
//Return found or not
bool YearIndex::matchYear(int inYear, int& location)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(YearIndex::my_list[i].year == inYear)
        {
            //Not conventional position in binary
            //but location in the list
            location = i;
            return true;
        } // end if
    } // end for

    return false;
} // end matchYear

//Search array of year indexes for the given year
//Return int array of keys if found
//Return an empty int array if not found
int * YearIndex::findYear(int inYear)
{
    int location;
    //Empty array to return if artist not found
    static int emptyArray[1];
    emptyArray[0] = 0;

    if(matchYear(inYear, location))
        return YearIndex::my_list[location].pos;
    return emptyArray;
} // End findYear

//Create a new resized array
//Delete old array
void YearIndex::resize()
{
    //Grow capacity 2 times
    int new_capacity = 2*capacity;
    //Create new list
    MINI * my_new = new MINI[new_capacity];
    //Default all spots
    for(int hold = 0; hold < new_capacity; ++hold)
    {
        my_new[hold].year = 0;
        for(int k = 0; k < 11; ++k)
            my_new[hold].pos[k] = 0;
    }
    //Fill in new list with current list items
    for(int i =0; i < capacity; ++i)
    {
        my_new[i] = my_list[i];
    }
    //Set capacity
    capacity = new_capacity;
    //Delete old list
    delete[] my_list;
    //Set new list
    my_list = my_new;
} // end resize

//Read sequential file and populate array
void YearIndex::readSecondary()
{
    std::ifstream input("my_year_index.txt");
    std::string line;
    getline (input,line);
    count = atoi(line.c_str());
    capacity = count + 1;
    my_list = new MINI[capacity];

    for(int hold = 0; hold < capacity; ++hold)
    {
        my_list[hold].year = 0;
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
        while(!input.eof() && position != capacity)
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

        input.close();
    } // end if
} // end readSecondary

//Write sequential file from array
void YearIndex::writeSecondary()
{
    std::ofstream fout("my_year_index.txt");
    int my_count = 0;
    for(int i = 1; i < capacity; ++i)
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
    for(int i = 1; i < capacity; ++i)
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
            fout << numOfKeys
                 << YearIndex::my_list[i].year
                 << buildLine
                 << std::endl;
        } // end if
    } //end for

    //Close file
    fout.close();
} // end writeSecondary
