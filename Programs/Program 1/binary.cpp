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
    return MyClass::title;
}
std::string MyClass::get_artist()
{
    return MyClass::artist;
}
std::string MyClass::get_type()
{
    return MyClass::type;
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
    //Stub
    return 0;
}

//Set functions
void MyClass::set_title(std::string my_title)
{
    MyClass::title = my_title;
}
void MyClass::set_artist(std::string my_artist)
{
    MyClass::artist = my_artist;
}
void MyClass::set_type(std::string my_type)
{
    MyClass::type = my_type;
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
    //Stub
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
void MyClass::writeIt(std::fstream* out, long position) const
{
     //write out the MyClass object
    out.seekp(position * (sizeof(MyClass)));
    out.write((char*) this, sizeof(MyClass));
}
void MyClass::readIt(std::fstream* input, long position) const
{
    //read in the MyClass object
    input.seekg(position * (sizeof(MyClass)));
    input.read((char*) this, sizeof(MyClass));
}
