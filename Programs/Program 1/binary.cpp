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
    //Stub
    return "";
}
std::string MyClass::get_artist()
{
    //Stub
    return "";
}
std::string MyClass::get_type()
{
    //Stub
    return "";
}
int MyClass::get_year() const
{
    //Stub
    return 0;
}
int MyClass::get_price() const
{
    //Stub
    return 0;
}
int MyClass::get_count() const
{
    //Stub
    return 0;
}
bool MyClass::get_flag() const
{
    //Stub
    return false;
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
    //Stub
}
void MyClass::set_artist(std::string my_artist)
{
    //Stub
}
void MyClass::set_type(std::string my_type)
{
    //Stub
}
void MyClass::set_year(int my_year)
{
    //Stub
}
void MyClass::set_price(int my_price)
{
    //Stub
}
void MyClass::set_count(int my_count)
{
    //Stub
}
// for setting zero record
void MyClass::set_value(std::fstream& inout, int value)
{
    //Stub
}
void MyClass::set_flag()
{
    //Stub
}
void MyClass::unset_flag()
{
    //Stub
}

// Read & write a File
void MyClass::writeIt(std::fstream* out, long position) const
{
    //Stub
}
void MyClass::readIt(std::fstream* input, long position) const
{
    //Stub
}
