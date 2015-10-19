/*
File       : main.cpp
Program    : Lab 5 - Using Stacks for a mouse maze
Due Date   : October 30..., 2015
Author     : Justin Kirk
Description: Lab 5...
*/

#include <iostream>
#include <stack>

struct MINI
{
    int x;
    int y;
} points;

std::ostream& operator<< (std::ostream &out, const MINI &p)
{
  out << p.x << " " << p.y << std::endl;
  return out;
}

using namespace std;

int main()
{
    stack<MINI> path;
    points.x = 1;
    points.y = 2;
    path.push(points);
     points.x = 5;
    points.y = 10;
    path.push(points);
    cout << path.;
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
