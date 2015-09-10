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
    PrimaryIndex::my_list[my_key].title = my_title;
    return true;
}
// The next 2 methods write the object out to a file or fill it from a read activity.
 void PrimaryIndex::writePrimary()
 {
     std::ofstream outPrimary ("primaryTitles.txt");

     for(int i = 1; i < 25; ++i)
     {
         outPrimary << PrimaryIndex::my_list[i].pos
                    << "#"
                    << PrimaryIndex::my_list[i].title
                    << std::endl;
     }

     outPrimary.close();

 }
 void PrimaryIndex::readPrimary()
 {

 }
void PrimaryIndex::change_title(std::string new_title, int key)
{
    PrimaryIndex::my_list[PrimaryIndex::count].title = new_title;
    PrimaryIndex::my_list[PrimaryIndex::count].pos = key;
}
int matchTitle(std::string inTitle)
{
    return 0;
}
