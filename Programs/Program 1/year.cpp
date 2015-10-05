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
}

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
}

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

    if(matchYear(inYear, location))
            return YearIndex::my_list[location].pos;
    return emptyArray;
} // End findYear

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
}




