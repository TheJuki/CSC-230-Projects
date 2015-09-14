/*
File       : bulk.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code for bulk
*/

#include "binary.h"
#include "artist.h"
#include "title.h"
#include <iostream>
#include <string>
#include<fstream>
#include <cstdlib>

//Prototypes
void build();
void checkBulkFile();

using namespace std;

//File names
char inputFileName[80] = "input.txt";
char outputFileName[80] = "output.bin";

void checkBulkFile()
{
    ifstream tryIt(outputFileName, ios::in);

    //If file does not exist, create it
    if(!tryIt)
    {
        //tryIt.close();
        build();
    }
    tryIt.close();

} // checkBulkFile

void build()
{
    //Open Sequential file for reading using ifstream
    ifstream input;
    input.open (inputFileName, fstream::in);

    if (input.is_open())
    {
        //Open Binary file for binary|writing using fstream
        fstream outputFile(outputFileName, ios::out | ios::binary);
        //Set position to 1
        long position = 1;
        //Create Primary Index object
        PrimaryIndex primaryInx;
        //Create Secondary Index object
        ArtistIndex secondaryInx;
        //delimiter is a space
        string delimiter = " ";
        //size of string
        size_t pos = 0;
        //Part of line
        int partNumber = 1;
        //Line in file as a string
        string line;
        //string of part
        string part;

        //----------------------------------------//
        //Parts of binary object in line variables
        string my_title, my_artist, my_type;
        int my_year, my_price, my_count;

        //while(not sequential.eof())
        while(!input.eof())
        {
            //Read in a line from the sequential file
            getline (input,line);

            //cout << line;

            //Defaults
            my_year = 0, my_price = 0, my_count = 0;
            my_title = "", my_artist = "", my_type = "";

            pos = 0;
            partNumber = 1;
            part = "";

            //Find each part separated by the delimiter and
            //Set the respective variables
            //Ex. TITLE ARTIST TYPE YEAR PRICE COUNT
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
                case(4) : my_year = std::atoi(part.c_str());
                    break;
                case(5) : my_price = std::atoi(part.c_str());
                    break;
                case(6) : my_count = std::atoi(part.c_str());
                    break;
                default: //None
                    break;
                } // end switch

                line.erase(0, pos + delimiter.length());
                partNumber++;
            } // end delimeter While

            //Convert line into binary file object named me
            MyClass me(my_title, my_artist, my_type,
               my_year, my_price, my_count);

            //Seek position and write record in binary file
            me.writeIt(outputFile, position);

            //Pass Primary Key information to Primary Index(title, position)
            primaryInx.set_title_key(my_title, position);

            //Pass Secondary Key information to Secondary Index(artist or year, position)
            secondaryInx.set_artist_key(my_artist, position);

            //position++
            position++;

        } // End eof while

        //Update Binary File record zero with count information
        MyClass writeZeroRecord;
        writeZeroRecord.set_value(outputFile, position);
        //Write Primary Index to a file (open file using ofstream)
        primaryInx.writePrimary();
        //Write Secondary Index to a file (open file using ofstream)
        secondaryInx.writeSecondary();

        //Close all files
        input.close();
        outputFile.close();

    } // End if


}
