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
    MyClass record1("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 1);
    record1.writeIt(outputFile, 1);

    //Record 2
    MyClass record2("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 2);
    record2.writeIt(outputFile, 2);

    //Record 3
    MyClass record3("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 3);
    record3.writeIt(outputFile, 3);

    //Record 4
    MyClass record4("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 4);
    record4.writeIt(outputFile, 4);

    //Record 5
    MyClass record5("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 5);
    record5.writeIt(outputFile, 5);

    //Record 6
    MyClass record6("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 6);
    record6.writeIt(outputFile, 6);

    //Record 7
    MyClass record7("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 7);
    record7.writeIt(outputFile, 7);
    outputFile.close();

}
