/*
File       : artist.h
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Header for artist.cpp
*/

#ifndef MY_ARTIST_INDEX_H
#define MY_ARTIST_INDEX_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
class ArtistIndex
{
private:
    struct MINI
    {
        std::string artist;
        int pos[11];
    } my_list[15];
    int count;

public:
    ArtistIndex(): count(0) //only a default constructor
    {
        for(int i = 1; i < 15; ++i)
        {
            my_list[i].artist = "0";
            for(int k = 0; k < 11; ++k)
                my_list[i].pos[k] = 0;
        }
    }

    std::string get_artist(int pos) const; // debugging tool

    void set_artist_key(std::string my_artist, int my_key);
    void updateArtist(std::string new_artist, int pos[]);

    //Read and Write
    void writeSecondary();
    void readSecondary();
    bool matchArtist(std::string inArtist, int pos[]);
};
#endif // MY_ARTIST_INDEX_H
