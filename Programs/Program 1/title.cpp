/*
File       : title.cpp
Program    : Program 1 - Dynamic Array Based Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"
#include <stdlib.h>

//Search array of title indexes for the given title
//Set pos to found key
//Return found or not
bool Primary::matchTitle(std::string inTitle, int& pos)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(Primary::my_list[i].title == inTitle)
        {
            pos = Primary::my_list[i].pos;
            return true;
        }
    }

    return false;
} // end matchTitle

//Search array of title indexes for the old title
//Set old title to new title
//Return found or not
bool Primary::updateTitle(std::string oldTitle, std::string newTitle, int pos)
{
   for(int i = 1; i < (count + 1); ++i)
    {
        if(Primary::my_list[i].title == oldTitle)
        {
            Primary::my_list[i].title = newTitle;
            return true;
        }
    }
    //Title not found
    return false;
} // end updateTitle

//Search array of title indexes for the given title
//Resize array if necessary
//Add new title index to the next position
//Return found or not
bool Primary::addTitle(std::string inTitle, int pos)
{
    if(Primary::matchTitle(inTitle, pos))
        return false;
    //Title does not exist so it is okay to add
    if((Primary::count + 1) == Primary::capacity)
    {
         Primary::resize();
    }

    int next_title = ++Primary::count;
    Primary::my_list[next_title].title = inTitle;
    Primary::my_list[next_title].pos = pos;
    return true;
} // end addTitle

//Search array of title indexes for the given title
//Default the title for deletion and set dead flag
//Return found or not
bool Primary::deleteTitle(std::string inTitle, int& pos)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(Primary::my_list[i].title == inTitle)
        {
            my_list[i].title = "****";
            my_list[i].pos = 0;
            my_list[i].dead_flag = true;
            //Set zero record to dead count
            my_list[0].title = "Dead_Count";
            setDeadCount(1);
            return true;
        }
    }
    //Title not found
    return false;
} // end deleteTitle

//Search array of title indexes for the given title
//Return found or not
bool Primary::printTitle(std::string inTitle, int& pos)
{
    if(Primary::matchTitle(inTitle, pos))
    {
        return true;
    }
    //Title not found
    return false;
} // end printTitle

//Get count
int Primary::getMaxCount()
{
    return count;
}
//Get dead count
int Primary::getDeadCount()
{
    return my_list[0].pos;
}
//Get capacity
int Primary::getCapacity()
{
    return capacity;
}
//Set dead count
void Primary::setDeadCount(int count)
{
    my_list[0].pos += count;
    dead_count += count;
}
//Create a new resized array
//Delete old array
void Primary::resize()
{
    //Grow capacity 2 times
    int new_capacity = 2*capacity;
    //Create new list
    MINI * my_new = new MINI[new_capacity];
    //Default all spots
    for(int hold = 0; hold < new_capacity; ++hold)
    {
        my_new[hold].title = "****";
        my_new[hold].pos = 0;
        my_new[hold].dead_flag = false;
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
