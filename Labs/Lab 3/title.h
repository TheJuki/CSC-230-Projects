/*
File       : title.h
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef MY_PRIMARY_H
#define MY_PRIMARY_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
class PrimaryIndex
{
private:
struct MINI { std::string title; int pos; } my_list[25];
int count;
 public:
 PrimaryIndex(): count(0) { // only a default constructor
for(int i = 1; i < 25; ++i) {
my_list[i].title = "0";
my_list[i].pos = 0;
}
}
bool set_title_key(std::string my_title, int my_key);
// The next 2 methods write the object out to a file or fill it from a read activity.
 void writePrimary();
 void readPrimary();
void change_title(std::string new_title, int key);
int matchTitle(std::string inTitle);
};
#endif
