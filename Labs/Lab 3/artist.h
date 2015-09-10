/*
File       : artist.h
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Header for artist.cpp
*/

#ifndef MY_SECONDARY_H
#define MY_SECONDARY_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
class SecondaryIndex
{
 private:
 struct MINI { std::string artist; int pos[11]; } my_list[15];
 int count;
 public:
 SecondaryIndex(): count(0) {
for(int i = 1; i < 15; ++i) {
my_list[i].artist = "0";
for(int k = 0; k < 11; ++k)
my_list[i].pos[k] = 0;
}
}
void set_artist_key(std::string my_artist, int my_key);
void updateArtist(std::string new_artist, int my_pos[]);
// The next 2 methods write the object out to a file or fill it from a read activity.
 void writeSecondary();
 void readSecondary();
bool matchArtist(std::string inArtist, int my_pos[]);
};
#endif
