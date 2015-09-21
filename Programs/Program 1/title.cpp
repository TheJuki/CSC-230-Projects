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
     for(int i = 1; i < 25; ++i)
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
     for(int i = 1; i < 25; ++i)
    {
         if(Primary::my_list[i].pos == pos)
         {
             Primary::my_list[i].title = newTitle;
             break;
         }
    }
}
bool Primary::addTitle(std::string inTitle, int pos)
{
    if(Primary::matchTitle(inTitle, pos))
        return true;
    //Title does not exist so it is okay to add
    //Max number of title indices is 25 (From 1 to 15)
    if((Primary::count + 1) != 25)
    {
        int next_title = ++Primary::count;
        Primary::my_list[next_title].title = inTitle;
        Primary::my_list[next_title].pos = pos;
    }
    return false;
}
bool Primary::deleteTitle(std::string inTitle, int& pos)
{

}
bool Primary::printTitle(std::string inTitle, int& pos)
{

}
