/*
File       : artist.h
Program    : Program 2 - Dynamic Array Indexes
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
    };
    MINI * my_list;
    int count, capacity;

public:
    ArtistIndex(): count(0), capacity(6) //only a default constructor
    {
        my_list = new MINI[capacity];

        for(int i = 1; i < capacity; ++i)
        {
            my_list[i].artist = "0";
            for(int k = 0; k < 11; ++k)
                my_list[i].pos[k] = 0;
        }
    }

    ArtistIndex(int new_capacity): count(0)
    {
        readSecondary();
    }

    ~ArtistIndex()
    {
        writeSecondary();
        delete[] my_list;
    }

    std::string get_artist(int pos) const; // debugging tool

    void addArtist(std::string my_artist, int my_key);
    void updateArtist(std::string old_artist, std::string new_artist);
    bool matchArtist(std::string inArtist, int& location);
    int * findArtist(std::string inArtist);
    bool deleteArtist(std::string inArtist, int pos);
    void readSecondary();
    void writeSecondary();

    void resize();
};
#endif // MY_ARTIST_INDEX_H
