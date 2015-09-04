/*
File       : bulk.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code for bulk
*/

#include "binary.h"
#include <fstream>
#include <iostream>
#include <string>

//Prototypes
void build();
void checkBulkFile();

using namespace std;

char outputFileName[80] = "output.txt";

void checkBulkFile()
{
    ifstream tryIt(outputFileName, ios::in);

    //If file does not exist, create it
    if(!tryIt)
    {
        tryIt.close();
        build();
    }
    tryIt.close();

} // checkBulkFile

void build()
{
    //Create output file
    fstream outputFile(outputFileName, ios::out | ios::binary);
    //Start at the first line
    outputFile.seekp(0);
    //Write 0 on the first line - zero record - count of records
    outputFile.write(0, 0);

    //Create a new record (Binary) to create 7 records
    MyClass record;

    //Record 1
    record.set_title("lustful   ");
    record.set_artist("Meirav Sher");
    record.set_type("Painting");
    record.set_year(2015);
    record.set_price(1500);
    record.set_count(1);
    record.writeIt(outputFile, 1);

    //Record 2
    record.set_title("Known face");
    record.set_artist("Falk Kastel");
    record.set_type("Drawing ");
    record.set_year(2014);
    record.set_price(1600);
    record.set_count(2);
    record.writeIt(outputFile, 2);

    //Record 3
    record.set_title("Atena     ");
    record.set_artist("Alberto Fus");
    record.set_type("Sculpture");
    record.set_year(2012);
    record.set_price(2200);
    record.set_count(3);
    record.writeIt(outputFile, 3);

    //Record 4
    record.set_title("Chanel    ");
    record.set_artist("Cate Parrl ");
    record.set_type("Painting ");
    record.set_year(2013);
    record.set_price(1500);
    record.set_count(4);
    record.writeIt(outputFile, 4);

    //Record 5
    record.set_title("woman w/peas");
    record.set_artist("Leonardo D.");
    record.set_type("Collage");
    record.set_year(2015);
    record.set_price(1300);
    record.set_count(5);
    record.writeIt(outputFile, 5);

    //Record 6
    record.set_title("Pokerface ");
    record.set_artist("Miss Aniela");
    record.set_type("Photography");
    record.set_year(2014);
    record.set_price(5495);
    record.set_count(6);
    record.writeIt(outputFile, 6);

    //Record 7
    record.set_title("Build Block");
    record.set_artist("Paul Brouns");
    record.set_type("Photography");
    record.set_year(2015);
    record.set_price(3300);
    record.set_count(7);
    record.writeIt(outputFile, 7);

    //Record 8 - Dead
    record.set_title("Test");
    record.set_artist("Dead");
    record.set_type("Flag");
    record.set_year(9999);
    record.set_price(9999);
    record.set_count(8);
    record.set_flag();
    record.writeIt(outputFile, 8);

    //Set final value - # of records
    record.set_value(outputFile, 8);

    //Close file
    outputFile.close();

}
