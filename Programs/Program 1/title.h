/*
File       : title.h
Program    : Program 1 - Dynamic Array Based Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef MY_PRIMARY_INDEX_H
#define MY_PRIMARY_INDEX_H
#include <fstream>
#include <string>
#include <iostream>

class Primary
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
    Primary(): count(0), dead_count(0), capacity(10)
    {
        my_list = new MINI[capacity];

        for(int hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }
    }
    Primary(int new_capacity): count(0), dead_count(0)
    {
        std::ifstream fin("my_primary_index.txt");
        fin >> count;
        capacity = count + 1;
        my_list = new MINI[capacity];

        for(int hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].title = "****";
            my_list[hold].pos = 0;
            my_list[hold].dead_flag = false;
        }

        for(int hold = 0; hold < capacity; ++hold)
        {
            fin >> my_list[hold].title >> my_list[hold].pos;
            my_list[hold].dead_flag = false;
        }
        fin.close();
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
        for(int hold = 0; hold < (count + 1); ++hold)
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
