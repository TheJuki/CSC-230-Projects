/*
File       : year.h
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Header for year.cpp
*/

#ifndef MY_YEAR_INDEX_H
#define MY_YEAR_INDEX_H
#include <iostream>
#include <fstream>

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

    void set_year_key(int my_year, int my_key);
    void updateYear(int new_year, int pos[]);

    //Read and Write
    void writeSecondary();
    void readSecondary();
    void matchYear(int inYear, int pos[]);
};
#endif // MY_YEAR_INDEX_H
