/*
File       : main.cpp
Program    : Lab 5 - Using Stacks for a mouse maze
Due Date   : October 30..., 2015
Author     : Justin Kirk
Description: Lab 5...
*/

#include <iostream>

using namespace std;

int main()
{
    //200 rows
    int rows = 200;
    //200 columns
    int columns = 200;
    //Initialize array
    char array[200][200];
    //Current line
    string line = "";

    //Counter for input row
    int counter = 0;

    //Set all cells to 0
    for (int r = 0; r < rows; ++r)
    {
        line = "";
        for (int c = 0; c < columns; ++c)
        {
            array[r][c]= '|';
        } // end for

    } // end for

    return 0;
}
