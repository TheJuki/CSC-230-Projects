/*
File       : title.cpp
Program    : Program 2 - Dynamic Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"
#include <stdlib.h>

//Search array of title indexes for the given title
//Set pos to found key
//Return found or not
bool TitleIndex::matchTitle(std::string inTitle, int& pos)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(TitleIndex::my_list[i].title == inTitle)
        {
            pos = TitleIndex::my_list[i].pos;
            return true;
        }
    }

    return false;
} // end matchTitle

//Search array of title indexes for the old title
//Set old title to new title
//Return found or not
bool TitleIndex::updateTitle(std::string oldTitle, std::string newTitle, int pos)
{
   for(int i = 1; i < (count + 1); ++i)
    {
        if(TitleIndex::my_list[i].title == oldTitle)
        {
            TitleIndex::my_list[i].title = newTitle;
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
bool TitleIndex::addTitle(std::string inTitle, int pos)
{
    if(TitleIndex::matchTitle(inTitle, pos))
        return false;
    //Title does not exist so it is okay to add
    if((TitleIndex::count + 1) == TitleIndex::capacity)
    {
         TitleIndex::resize();
    }

    int next_title = ++TitleIndex::count;
    TitleIndex::my_list[next_title].title = inTitle;
    TitleIndex::my_list[next_title].pos = pos;
    return true;
} // end addTitle

//Search array of title indexes for the given title
//Default the title for deletion and set dead flag
//Return found or not
bool TitleIndex::deleteTitle(std::string inTitle)
{
    for(int i = 1; i < (count + 1); ++i)
    {
        if(TitleIndex::my_list[i].title == inTitle)
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
bool TitleIndex::printTitle(std::string inTitle, int& pos)
{
    if(TitleIndex::matchTitle(inTitle, pos))
    {
        return true;
    }
    //Title not found
    return false;
} // end printTitle

//Get count
int TitleIndex::getMaxCount()
{
    return count;
}
//Get dead count
int TitleIndex::getDeadCount()
{
    return my_list[0].pos;
}
//Get capacity
int TitleIndex::getCapacity()
{
    return capacity;
}
//Set dead count
void TitleIndex::setDeadCount(int count)
{
    my_list[0].pos += count;
    dead_count += count;
}
//Create a new resized array
//Delete old array
void TitleIndex::resize()
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

//Read sequential file and populate array
void TitleIndex::readPrimary()
{
    std::ifstream fin("my_primary_index.txt");
        fin >> count;
        capacity = count + 5;
        my_list = new MINI[capacity];

        for(int hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }

        for(int hold = 0; hold < capacity; ++hold)
        {
            fin >> my_list[hold].title >> my_list[hold].pos;
            my_list[hold].dead_flag = false;
        }
        fin.close();
} // end readPrimary

//Write sequential file from array
void TitleIndex::writePrimary()
{
    std::ofstream fout("my_primary_index.txt");
        int my_count = 0;
        for(int i = 1; i < capacity; ++i)
        {
            if(my_list[i].pos != 0 && !my_list[i].dead_flag)
            {
                ++my_count;
            }
        }
        fout << my_count << std::endl;
        for(int hold = 0; hold < (count + 1); ++hold)
        {
            if(!my_list[hold].dead_flag)
                fout << my_list[hold].title << " "
                     << my_list[hold].pos << std::endl;
        }
        fout.close();
} // end writePrimary

