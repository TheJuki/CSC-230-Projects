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
#include <sstream>
#include <stdlib.h>

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
        std::ifstream input("my_year_index.txt");
        std::string line;
        getline (input,line);
        count = atoi(line.c_str());
        capacity = count + 1;
        my_list = new MINI[capacity];

        for(int hold = 0; hold < capacity; ++hold)
        {
            my_list[hold].year = 0;
            for(int k = 0; k < 11; ++k)
                my_list[hold].pos[k] = 0;
        }

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
            //Number of keys in line
            int numOfKeys = 0;

            //while(not sequential.eof())
            while(!input.eof() && position != capacity)
            {
                //Read in a line from the sequential file
                getline (input,line);

                //cout << line;

                //Defaults
                pos = 0;
                part = "";
                numOfKeys = 0;

                //Get Number of keys
                if ((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    line.erase(0, pos + delimiter.length());
                    numOfKeys = atoi(part.c_str());
                    YearIndex::my_list[position].pos[0] = numOfKeys;
                }
                //Get year
                if ((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    line.erase(0, pos + delimiter.length());
                    YearIndex::my_list[position].year = atoi(part.c_str());
                }
                //Set pos to keys in line
                for(int i = 1; i < (numOfKeys + 1); ++i)
                {
                    if((pos = line.find(delimiter)) != std::string::npos)
                    {
                        part = line.substr(0, pos);
                        YearIndex::my_list[position].pos[i] = atoi(part.c_str());
                        line.erase(0, pos + delimiter.length());
                    }
                }

                //position++
                position++;

            } // End eof while

            input.close();
        } // end if
    }

    ~YearIndex()
    {
        std::ofstream fout("my_year_index.txt");
        int my_count = 0;
        for(int i = 1; i < capacity; ++i)
        {
            if(my_list[i].pos[0] != 0)
            {
                ++my_count;
            }
        }
        fout << my_count << std::endl;

        //A normal string used as a string builder
        std::string buildLine;
        std::string numOfKeys;

        //For each item in my_list
        for(int i = 1; i < capacity; ++i)
        {
            //Default
            buildLine = " ";

            //Number of Keys
            std::stringstream strs;
            strs << YearIndex::my_list[i].pos[0];
            std::string temp_str = strs.str();
            //Add number of keys to numOfKeys
            numOfKeys = temp_str + " ";

            //for each item in pos
            for(int k = 1; k < 11; ++k)
            {
                if(YearIndex::my_list[i].pos[k] != 0)
                {
                    //Convert the key to a string
                    std::stringstream strs;
                    strs << YearIndex::my_list[i].pos[k];
                    std::string temp_str = strs.str();
                    //Add key to buildLine
                    buildLine += temp_str + " ";
                } //end if
            } // end for

            //If there is at least 1 key then write to file
            if(YearIndex::my_list[i].pos[0] != 0)
            {
                //Write to file
                fout << numOfKeys
                     << YearIndex::my_list[i].year
                     << buildLine
                     << std::endl;
            } // end if
        } //end for

        //Close file
        fout.close();
        delete[] my_list;
    }

    int get_year(int pos) const; // debugging tool

    void addYear(int my_year, int my_key);
    void updateYear(int old_year, int new_year);

    bool matchYear(int inYear, int& location);
    int * findYear(int inYear);
    bool deleteYear(int inYear, int pos);
    void resize();
};
#endif // MY_YEAR_INDEX_H
