/*
File       : title.h
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Title - Primary Index
*/

#include "title.h"

bool PrimaryIndex::set_title_key(std::string my_title, int my_key)
{
    //Check for an existing title
    bool foundTitle = false;
     //For each item in my_list
    for(int i = 1; i < 25; ++i)
    {
        if(PrimaryIndex::my_list[i].title.compare(my_title) == 0)
        {
            //Existing title exists
            return true;
        }
    }
    //Title does not exist so it is okay to add
    //Max number of title indices is 25 (From 1 to 15)
    if((PrimaryIndex::count + 1) != 25)
    {
        int next_title = ++PrimaryIndex::count;
        PrimaryIndex::my_list[next_title].title = my_title;
        PrimaryIndex::my_list[next_title].pos = my_key;
    }
    return false;
} // end PrimaryIndex

// The next 2 methods write the object out to a file or fill it from a read activity.
 void PrimaryIndex::writePrimary()
 {
     //Sequential file for Primary indices
     std::ofstream outPrimary ("primaryTitles.txt");

     //For each item in my_list
     for(int i = 1; i < 25; ++i)
     {
         //If there is at least 1 key then write to file
         if(PrimaryIndex::my_list[i].pos != 0)
         {
               outPrimary << PrimaryIndex::my_list[i].pos
                    << " "
                    << PrimaryIndex::my_list[i].title
                    << std::endl;
         }
     }
     //Close file
     outPrimary.close();
 } // end writePrimary

 void PrimaryIndex::readPrimary()
 {
    // stub
 }
void PrimaryIndex::change_title(std::string new_title, int key)
{
    //Stub
}
int matchTitle(std::string inTitle)
{
    return 0;
}
