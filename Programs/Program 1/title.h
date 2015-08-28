/*
File       : title.h
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef MY_PRIMARY_INDEX_H
#define MY_PRIMARY_INDEX_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

class PrimaryIndex
{
private:
    struct MINI
    {
        std::string title;
        int tag;
    } my_list[25];
    int count;

public:
    PrimaryIndex(): count(0) //only a default constructor
    {
        for(int i = 1; i < 25; ++i)
        {
            my_list[i].title = "0";
            my_list[i].tag = 0;
        }
    }

    bool set_title_key(std::string my_title, int my_key);

    //Read and Write
    void writePrimary();
    void readPrimary();
    void outputKey(); // debugging tool
    void change_title(std::string new_title, int key);
    void matchTitle(std::string inTitle);
};
#endif // MY_PRIMARY_INDEX_H
