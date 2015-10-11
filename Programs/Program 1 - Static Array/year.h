/*
File       : year.h
Program    : Program 1 - Static Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Header for year.cpp
*/

#ifndef MY_YEAR_INDEX_H
#define MY_YEAR_INDEX_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

class YearIndex
{
private:
    struct MINI
    {
        int year;
        int pos[11];
    } my_list[15];
    int count;

public:
    YearIndex(): count(0) //only a default constructor
    {
        for(int i = 1; i < 15; ++i)
        {
            my_list[i].year = 0;
            for(int k = 0; k < 11; ++k)
                my_list[i].pos[k] = 0;
        }
    }

    int get_year(int pos) const; // debugging tool

    void addYear(int my_year, int my_key);
    void updateYear(int old_year, int new_year);

    bool matchYear(int inYear, int& location);
    int * findYear(int inYear);
    bool deleteYear(int inYear, int pos);
    void readSecondary();
    void writeSecondary();
};
#endif // MY_YEAR_INDEX_H

