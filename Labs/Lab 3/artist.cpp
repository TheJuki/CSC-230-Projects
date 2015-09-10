/*
File       : artist.cpp
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"
#include<iostream>
#include<fstream>

void SecondaryIndex::set_artist_key(std::string my_artist, int my_key)
{
    SecondaryIndex::my_list[my_key].artist = my_artist;
}

void SecondaryIndex::updateArtist(std::string new_artist, int pos[])
{
    SecondaryIndex::my_list[SecondaryIndex::count].artist = new_artist;
    for(int i = 1; i < 15; ++i)
         SecondaryIndex::my_list[SecondaryIndex::count].pos[i] = pos[i];

}

void SecondaryIndex::writeSecondary()
{
   std::ofstream outSecondary ("secondaryArtists.txt");

     for(int i = 1; i < 25; ++i)
     {
         outSecondary << SecondaryIndex::my_list[i].pos
                    << "#"
                    << SecondaryIndex::my_list[i].artist
                    << std::endl;
     }

     outSecondary.close();
}

void SecondaryIndex::readSecondary()
{
    // Stub
}

bool SecondaryIndex::matchArtist(std::string inArtist, int pos[])
{
    return false;
}


