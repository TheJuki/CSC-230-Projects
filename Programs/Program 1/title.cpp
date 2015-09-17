/*
File       : title.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"
#include <stdlib.h>

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
} // end set_title_key

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
     //Open Sequential file for reading using ifstream
    std::ifstream input;
    input.open ("primaryTitles.txt", std::fstream::in);

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

        //while(not sequential.eof())
        while(!input.eof())
        {
            //Read in a line from the sequential file
            getline (input,line);

            //cout << line;

            //Defaults
            pos = 0;
            part = "";

            //Get key
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                 part = line.substr(0, pos);
                 line.erase(0, pos + delimiter.length());
                 int key = atoi(part.c_str());
                 PrimaryIndex::my_list[position].pos = key;
            }
            //Get artist
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                 part = line.substr(0, pos);
                 line.erase(0, pos + delimiter.length());
                 PrimaryIndex::my_list[position].title = atoi(part.c_str());
            }

            //position++
            position++;

        } // End eof while

        //Set zero record to number of indexes
        my_list[0].pos = position;
        //Close all files
        input.close();
    } // end if
} //end readPrimary

void PrimaryIndex::outputKey()
{
    std::cout << PrimaryIndex::my_list[0].pos;
}

void PrimaryIndex::change_title(std::string new_title, int key)
{
    for(int i = 1; i < 25; ++i)
    {
         if(PrimaryIndex::my_list[i].pos == key)
         {
             PrimaryIndex::my_list[i].title = new_title;
             break;
         }
    }
}

int PrimaryIndex::matchTitle(std::string inTitle)
{
    int location, count;

    for (location = 1; location <= PrimaryIndex::my_list[0].pos; ++location)
    {
        if(PrimaryIndex::my_list[location].title == inTitle)
        {
            return 1;
        }
    }
    return 0;
}
