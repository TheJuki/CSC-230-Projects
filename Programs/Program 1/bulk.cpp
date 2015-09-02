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

using namespace std;

const string fileName = "output.txt";

void build()
{
    fstream outputFile(fileName, ios::out | ios::binary);

    MyClass record = new MyClass("Mona Lisa", "Leonardo D.", "Painting", 1212, 123, 1);
    record.writeIt(outputFile, 1);
    record.delete();


}
