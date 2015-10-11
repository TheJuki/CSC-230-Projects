/*
File       : title.cpp
Program    : Program 1 - Static Array Indexes
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
    if((TitleIndex::count + 1) != 25)
    {
        int next_title = ++TitleIndex::count;
        TitleIndex::my_list[next_title].title = inTitle;
        TitleIndex::my_list[next_title].pos = pos;
    }
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

//Set dead count
void TitleIndex::setDeadCount(int count)
{
    my_list[0].pos += count;
    dead_count += count;
}

//Read sequential file and populate array
void TitleIndex::readPrimary()
{
    std::ifstream fin("my_primary_index.txt");
    fin >> count;

    for(int hold = 0; hold < 25; ++hold)
    {
        my_list[hold].title = "****";
        my_list[hold].pos = 0;
        my_list[hold].dead_flag = false;
    }

    for(int hold = 0; hold < 25; ++hold)
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
    for(int i = 1; i < 25; ++i)
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

