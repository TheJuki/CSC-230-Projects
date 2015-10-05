/*
File       : title.h
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef MY_PRIMARY_INDEX_H
#define MY_PRIMARY_INDEX_H
#include <fstream>
#include <string>
#include <iostream>

struct MINI
{
    std::string title;
    int pos;
    bool dead_flag;
};

class Primary
{

private:
    struct MINI * my_list;
    int count, dead_count, hold, max_count, capacity;

public:
    Primary(): count(0), dead_count(0), max_count(0), capacity(11)
    {
        my_list = new MINI[capacity];

        for(hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }
    }
    Primary(int my_hold): count(0), dead_count(0), hold(my_hold)
    {
        std::ifstream fin("my_primary_index.txt");
        fin >> max_count;
        count = max_count;
        capacity = max_count + 1;
        my_list = new MINI[capacity];

        for(hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }

        for(hold = 0; hold < capacity; ++hold)
        {
            fin >> my_list[hold].title >> my_list[hold].pos;
            my_list[hold].dead_flag = false;
        }
    }

    ~Primary()
    {
        std::ofstream fout("my_primary_index.txt");
        int my_count = 0;
        for(int i = 1; i < capacity; ++i)
        {
            if(my_list[i].pos != 0 && !my_list[i].dead_flag)
            {
                ++my_count;
            }
        }
        fout << my_count << std::endl;
        for(hold =0; hold < (count + 1); ++hold)
        {
            if(!my_list[hold].dead_flag)
                fout << my_list[hold].title << " "
                     << my_list[hold].pos << std::endl;
        }
        fout.close();
        delete[] my_list;
    }
    bool matchTitle(std::string, int&);
    bool updateTitle(std::string /*old title*/, std::string /*new title*/, int /*pos in binary*/);
    bool addTitle(std::string, int);
    bool deleteTitle(std::string, int&);
    bool printTitle(std::string, int&);
    int getMaxCount();
    int getDeadCount();
    void setDeadCount(int count);
    int getCapacity();
    void resize();

};
#endif // MY_PRIMARY_INDEX_H
