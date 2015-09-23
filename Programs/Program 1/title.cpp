/*
File       : title.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"
#include <stdlib.h>

bool Primary::matchTitle(std::string inTitle, int& pos)
{
     for(int i = 1; i < MAX_LIMIT; ++i)
    {
        if(Primary::my_list[i].title == inTitle)
        {
            pos = i;
            return true;
        }
    }

    return false;
}
bool Primary::updateTitle(std::string oldTitle, std::string newTitle, int pos)
{
    if(Primary::matchTitle(oldTitle, pos))
    {
        Primary::my_list[pos].title = newTitle;
        return true;
    }
    //Title not found
    return false;
}
bool Primary::addTitle(std::string inTitle, int pos)
{
    if(Primary::matchTitle(inTitle, pos))
        return false;
    //Title does not exist so it is okay to add
    if((Primary::max_count + 1) != MAX_LIMIT)
    {
        int next_title = ++Primary::max_count;
        Primary::my_list[next_title].title = inTitle;
        Primary::my_list[next_title].pos = pos;
        return true;
    }
    return false;
}
bool Primary::deleteTitle(std::string inTitle, int& pos)
{
    if(Primary::matchTitle(inTitle, pos))
    {
        my_list[pos].title = "****";
        my_list[pos].pos = 0;
        my_list[pos].dead_flag = true;
        return true;
    }
    //Title not found
    return false;
}
bool Primary::printTitle(std::string inTitle, int& pos)
{
    if(Primary::matchTitle(inTitle, pos))
    {
        return true;
    }
    //Title not found
    return false;
}
