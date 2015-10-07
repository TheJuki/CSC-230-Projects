/*
File       : binary.h
Program    : Program 1 - Dynamic Array Based Indexes
Due Date   : October 12, 2015
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

    //Default constructor
    MyClass(): year(0), price(0), count(0), dead_flag(false)
    {
        strcpy(title, "0"); //Using Code::Blocks
        strcpy(artist, "0");
        strcpy(type, "0");
    }

    //Constructor
    MyClass(std::string my_title, std::string my_artist, std::string my_type,
            int my_year, int my_price, int my_count): year(my_year),
        price(my_price), count(my_count), dead_flag(false)
    {
        strcpy(title, my_title.c_str()); //Using Code::Blocks
        strcpy(artist, my_artist.c_str());
        strcpy(type, my_type.c_str());
    }

    //Destructor
    ~MyClass(){}

    //Get functions
    std::string get_title();
    std::string get_artist();
    std::string get_type();
    int get_year() const;
    int get_price() const;
    int get_count() const;
    bool get_flag() const;
    int get_value(std::fstream& inout); // for getting the value from zero record

    //Set functions
    void set_title(std::string my_title);
    void set_artist(std::string my_artist);
    void set_type(std::string my_type);
    void set_year(int my_year);
    void set_price(int my_price);
    void set_count(int my_count);
    void set_value(std::fstream& inout, int value); // for setting zero record
    void set_flag();
    void unset_flag();

    // Read & write a File
    void writeIt(std::fstream& out, long position) const;
    void readIt(std::fstream& input, long position) const;

    //Update
    void deleteRecord(std::fstream& file, int pos, std::string& artist, int& year, std::string& title);

    friend std::ostream& operator <<(std::ostream& out, const MyClass& me);
};
#endif // CLASS_H
