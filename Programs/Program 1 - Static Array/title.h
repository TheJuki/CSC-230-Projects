/*
File       : title.h
Program    : Program 1 - Static Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef MY_PRIMARY_INDEX_H
#define MY_PRIMARY_INDEX_H
#include <fstream>
#include <string>
#include <iostream>

class TitleIndex
{

private:
    struct MINI
    {
        std::string title;
        int pos;
        bool dead_flag;
    } my_list[25];
    int count, dead_count;

public:
    TitleIndex(): count(0), dead_count(0)
    {
        for(int hold = 0; hold < 25; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }
    }

    TitleIndex(int read): count(0), dead_count(0)
    {
        readPrimary();
    }

    bool matchTitle(std::string, int&);
    bool updateTitle(std::string /*old title*/, std::string /*new title*/, int /*pos in binary*/);
    bool addTitle(std::string, int);
    bool deleteTitle(std::string);
    bool printTitle(std::string, int&);
    int getMaxCount();
    int getDeadCount();
    void setDeadCount(int count);
    void readPrimary();
    void writePrimary();
    void outputKey(); //Debug

};
#endif // MY_PRIMARY_INDEX_H

