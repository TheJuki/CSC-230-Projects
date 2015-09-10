/*
File       : main.cpp
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Main driver file
*/

#include <string>
using namespace std;

//File names
string

//Open Sequential file for reading using ifstream
string line;
ifstream input("input.txt");

if (input.is_open())
{
    while (getline(input,line))
    {
        cout << line << enl;
    }
    input.close();
}
else
{
    cout << "Unable to open file";
}

    string delimiter = "#";

    size_t pos = 0;

    //Part of line
    int partNumber = 1;

    string part;
    while ((pos = line.find(delimiter)) != string::npos) {
        part = line.substr(0, pos);
        cout << part << std::endl;
        line.erase(0, pos + delimiter.length());
    }
//Open Binary file for binary|writing using fstream
fstream outputFile(outputFileName, ios::out | ios::binary);
//Set position to 1
//Read in a line from the sequential file

//Create binary object
//Create Primary Index object
//Create Secondary Index object

//while(not sequential.eof())

//Convert line into binary file object
//Seek position and write record in binary file
//Pass Primary Key information to Primary Index(title, position)
//Pass Secondary Key information to Secondary Index(artist or year, position)
//position++
//Read in another line from Sequential file

//Update Binary File record zero with count information
//Write Primary Index to a file (open file using ofstream)
//Write Secondary Index to a file (open file using ofstream)
//Close all files

