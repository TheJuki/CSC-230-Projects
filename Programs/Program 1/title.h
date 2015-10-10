/*
File       : title.h
Program    : Program 2 - Dynamic Array Indexes
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
    };
    MINI * my_list;
    int count, dead_count, capacity;

public:
    TitleIndex(): count(0), dead_count(0), capacity(10)
    {
        my_list = new MINI[capacity];

        for(int hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }
    }
    TitleIndex(int new_capacity): count(0), dead_count(0)
    {
        readPrimary();
    }

    ~TitleIndex()
    {
        writePrimary();
        delete[] my_list;
    }
    bool matchTitle(std::string, int&);
    bool updateTitle(std::string /*old title*/, std::string /*new title*/, int /*pos in binary*/);
    bool addTitle(std::string, int);
    bool deleteTitle(std::string);
    bool printTitle(std::string, int&);
    int getMaxCount();
    int getDeadCount();
    void setDeadCount(int count);
    int getCapacity();
    void resize();
    void readPrimary();
    void writePrimary();

};
#endif // MY_PRIMARY_INDEX_H
