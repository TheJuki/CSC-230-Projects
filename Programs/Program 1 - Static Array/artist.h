/*
File       : artist.h
Program    : Program 1 - Static Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Header for artist.cpp
*/

#ifndef MY_ARTIST_INDEX_H
#define MY_ARTIST_INDEX_H
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

    ArtistIndex(int read): count(0)
    {
        readSecondary();
    }


    std::string get_artist(int pos) const; // debugging tool

    void addArtist(std::string my_artist, int my_key);
    void updateArtist(std::string old_artist, std::string new_artist);
    bool matchArtist(std::string inArtist, int& location);
    int * findArtist(std::string inArtist);
    bool deleteArtist(std::string inArtist, int pos);
    void readSecondary();
    void writeSecondary();
};
#endif // MY_ARTIST_INDEX_H

