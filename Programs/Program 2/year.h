/*
File       : year.h
Program    : Program 2 - Dynamic Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Header for year.cpp
*/

#ifndef MY_YEAR_INDEX_H
#define MY_YEAR_INDEX_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class YearIndex
{
private:
    struct MINI
    {
        int year;
        int pos[11];
    };
    MINI * my_list;
    int count, capacity;

public:
    YearIndex(): count(0), capacity(6) //only a default constructor
    {
        my_list = new MINI[capacity];

        for(int i = 1; i < capacity; ++i)
        {
            my_list[i].year = 0;
            for(int k = 0; k < 11; ++k)
                my_list[i].pos[k] = 0;
        }
    }
    YearIndex(int new_capacity): count(0)
    {
        readSecondary();
    }

    ~YearIndex()
    {
        writeSecondary();
        delete[] my_list;
    }

    int get_year(int pos) const; // debugging tool

    void addYear(int my_year, int my_key);
    void updateYear(int old_year, int new_year);

    bool matchYear(int inYear, int& location);
    int * findYear(int inYear);
    bool deleteYear(int inYear, int pos);
    void resize();
    void readSecondary();
    void writeSecondary();
};
#endif // MY_YEAR_INDEX_H
