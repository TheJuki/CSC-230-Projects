/*
File       : binary.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code for binary file handling
*/

#include "binary.h"

//Get functions
std::string MyClass::get_title()
{
    return std::string(MyClass::title);
}
std::string MyClass::get_artist()
{
    return std::string(MyClass::artist);
}
std::string MyClass::get_type()
{
    return std::string(MyClass::type);
}
int MyClass::get_year() const
{
    return MyClass::year;
}
int MyClass::get_price() const
{
    return MyClass::price;
}
int MyClass::get_count() const
{
    return MyClass::count;
}
bool MyClass::get_flag() const
{
    return MyClass::dead_flag;
}
// for getting the value from zero record
int MyClass::get_value(std::fstream& inout)
{
    char* value;
    strcpy(value, "0");
    inout.seekg(0);
    inout.read(value, 0);
    return int(value);
}

//Set functions
void MyClass::set_title(std::string my_title)
{
     strcpy(MyClass::title, my_title.c_str());
}
void MyClass::set_artist(std::string my_artist)
{
    strcpy(MyClass::artist, my_artist.c_str());
}
void MyClass::set_type(std::string my_type)
{
    strcpy(MyClass::type, my_type.c_str());
}
void MyClass::set_year(int my_year)
{
    MyClass::year = my_year;
}
void MyClass::set_price(int my_price)
{
    MyClass::price = my_price;
}
void MyClass::set_count(int my_count)
{
    MyClass::count = my_count;
}
// for setting zero record
void MyClass::set_value(std::fstream& inout, int value)
{
    inout.seekp(0);
    char* writeOut = (char*)MyClass::count;
    inout.write(writeOut, 0);
}
void MyClass::set_flag()
{
    MyClass::dead_flag = true;
}
void MyClass::unset_flag()
{
    MyClass::dead_flag = false;
}

// Read & write a File
void MyClass::writeIt(std::fstream& out, long position) const
{
     //write out the MyClass object
    out.seekp(position * (sizeof(MyClass)));
    out.write((char*) this, sizeof(MyClass));
}
void MyClass::readIt(std::fstream& input, long position) const
{
    //read in the MyClass object
    input.seekg(position * (sizeof(MyClass)));
    input.read((char*) this, sizeof(MyClass));
}

std::ostream& operator <<(std::ostream& out, const MyClass& me)
{
    out << me.artist << std::endl;
    return out;
}
