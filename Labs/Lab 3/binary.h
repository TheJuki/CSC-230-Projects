/*
File       : binary.h
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Header for binary.cpp
*/

#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <cstring>
#include <fstream>
class MyClass
{
 private:
    char title[35], artist[25], type[12];
    int year, price, count;
    bool dead_flag;
 public:
     MyClass(): year(0), price(0), count(0), dead_flag(false)
    {
        strcpy(title, "0"); // remove _s for non-VS programs
        strcpy(artist, "0");
        strcpy(type, "0");
    }
    MyClass(std::string my_title, std::string my_artist, std::string my_type,
    int my_year, int my_price, int my_count): year(my_year),
    price(my_price), count(my_count), dead_flag(false)
    {
        strcpy(title, my_title.c_str());
        strcpy(artist, my_artist.c_str());
        strcpy(type, my_type.c_str());
    }
     std::string get_title();
    std::string get_artist();
    std::string get_type();
    int get_year() const;
    int get_price() const;
    int get_count() const;
    bool get_flag() const;
    void set_title(std::string my_title);
    void set_artist(std::string my_artist);
    void set_type(std::string my_type);
    void set_year(int my_year);
    void set_price(int my_price);
    void set_count(int my_count);
    void set_value(std::fstream& inout, int value);
    void set_flag();
    void unset_flag();
    // The next two methods write the object out to a file or fill it from a read
    // activity. position & read or position & write could be combined
    void set_and_writeIt(std::fstream& out, long recordNumber);
    void set_and_readIt(std::fstream& input, long recordNumber);
     friend std::ostream& operator<<(std::ostream& out, const MyClass& someObject);
};
#endif

