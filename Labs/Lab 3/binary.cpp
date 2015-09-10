/*
File       : binary.cpp
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Binary object - A record in the binary file
*/

#include "binary.h"
#include <stdlib.h>
#include <sstream>
#include <string>

std::string MyClass::get_title()
{
    return std::string(MyClass::title);
}
std::string MyClass::get_artist()
{
     return std::string(MyClass::title);
}
std::string MyClass::get_type()
{
     return std::string(MyClass::title);
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
void MyClass::set_value(std::fstream& inout, int value)
{
    inout.seekp(0);
    std::stringstream strs;
    strs << value;
    std::string temp_str = strs.str();
    char* writeOut = (char*) temp_str.c_str();
    inout.write((char*) writeOut, 80);
}
void MyClass::set_flag()
{
    MyClass::dead_flag = true;
}
void MyClass::unset_flag()
{
    MyClass::dead_flag = false;
}
// The next two methods write the object out to a file or fill it from a read
// activity. position & read or position & write could be combined
void MyClass::set_and_writeIt(std::fstream& out, long recordNumber)
{
    //write out the MyClass object
    out.seekp(recordNumber * (sizeof(MyClass)));
    out.write((char*) this, sizeof(MyClass));
}
void MyClass::set_and_readIt(std::fstream& input, long recordNumber)
{
    //read in the MyClass object
    input.seekg(recordNumber * (sizeof(MyClass)));
    input.read((char*) this, sizeof(MyClass));
}

std::ostream& operator<<(std::ostream& out, const MyClass& someObject)
 {
    std::string dead = "Available";
    if(someObject.dead_flag)
        dead = "N/A";
    out << "  " << someObject.title
        << "  " << someObject.artist
        << "   " << someObject.type
        << "     " << someObject.year
        << "     $" << someObject.price
        << "     $" << someObject.count
        << "     "  << dead
        << std::endl;
    return out;
 }
