/*
File       : main.cpp
Program    : Lab 3 - Create Binary File from Sequential File
Due Date   : September 12, 2015
Author     : Justin Kirk
Description: Main driver file
*/

#include "binary.h"
#include "artist.h"
#include "title.h"
#include <string>
#include<iostream>
#include<fstream>

using namespace std;

//File names
char inputFileName[80] = "input.txt";
char outputFileName[80] = "output.bin";

int main ()
{

    //Open Sequential file for reading using ifstream
    string line;
    ifstream input(inputFileName);

    if (input.is_open())
    {


    /*
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
        */
    //Open Binary file for binary|writing using fstream
    fstream outputFile(outputFileName, ios::out | ios::binary);
    //Set position to 1
    int position = 1;
    //Read in a line from the sequential file

    //Create binary object
     //MyClass myObject;
    //Create Primary Index object
    PrimaryIndex primaryInx;
    //Create Secondary Index object
    SecondaryIndex secondaryInx;
    //delimiter is #
    string delimiter = "#";
    //size of string
    size_t pos = 0;
    //Part of line
    int partNumber = 1;
    //string of part
    string part;

    //----------------------------------------//
    //Parts of binary object in line variables
    string my_title, my_artist, my_type;
    int my_year, my_price, my_count;

    //while(not sequential.eof())
    while(!input.eof())
    {
        //Defaults
        my_year = 0, my_price = 0, my_count = 0;
        my_title = "", my_artist = "", my_type = "";

        pos = 0;
        partNumber = 1;
        part = "";

        //Find each part separated by the delimiter and
        //Set the respective variables
        //Ex. TITLE#ARTIST#TYPE#YEAR#PRICE#COUNT
        while ((pos = line.find(delimiter)) != string::npos) {
            part = line.substr(0, pos);
            switch (partNumber)
            {
            case(1) : my_title = part;
                break;
            case(2) : my_artist = part;
                break;
            case(3) : my_type = part;
                break;
            case(4) : my_year = part;
                break;
            case(5) : my_price = part;
                break;
            case(6) : my_count = part;
                break;
            default: //None
                break;
            } // end switch
            line.erase(0, pos + delimiter.length());
            partNumber++;
        }

        //Convert line into binary file object
        MyClass myObject(my_title, my_artist, my_type,
           my_year, my_price, my_count);
        //Seek position and write record in binary file
        myObject.set_and_writeIt(input, position);
        //Pass Primary Key information to Primary Index(title, position)
        primaryInx.count = position;
        primaryInx.change_title(my_title, position);
        //Pass Secondary Key information to Secondary Index(artist or year, position)
        //position++
        position++;
    }





    //Read in another line from Sequential file

    //Update Binary File record zero with count information
    //Write Primary Index to a file (open file using ofstream)
    //Write Secondary Index to a file (open file using ofstream)
    //Close all files
    input.close();
    }
    return 0;
}

