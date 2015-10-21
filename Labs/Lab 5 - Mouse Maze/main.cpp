/*
File       : main.cpp
Program    : Lab 5 - Using Stacks for a mouse maze
Due Date   : October 30..., 2015
Author     : Justin Kirk
Description: Lab 5...
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>

void setupMaze(char mazeArray[][200]);

struct MINI
{
    int x;
    int y;
} points;

struct Mouse
{
    int x;
    int y;
} mouse;

std::ostream& operator<< (std::ostream &out, const MINI &p)
{
    out << p.x << " " << p.y << std::endl;
    return out;
}

using namespace std;

int main()
{
    stack<MINI> path;
    /*
    points.x = 1;
    points.y = 2;
    path.push(points);
     points.x = 5;
    points.y = 10;
    path.push(points);
    path.pop();
    path.pop();
    cout << path.size();
    */
    //200 rows
    int rows = 200;
    //200 columns
    int columns = 200;
    //Initialize array
    char mazeArray[200][200];
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
            mazeArray[r][c]= '0';
        } // end for
    } // end for

    setupMaze(mazeArray);
    cout << mazeArray[1][1] << endl;

    return 0;
}

void setupMaze(char mazeArray[][200])
{
    std::ifstream input("input.txt");

    if (input.is_open())
    {
         int rowCount = 0;
        int columnCount = 0;
        input >> rowCount >> columnCount;
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;

        //Get MAZE
        for(int i = 0; i < rowCount+1; ++i)
        {
            getline (input,line);

            for(int k = 0; k < columnCount+1; ++k)
            {
                part = line.substr(0, 1);
                mazeArray[i][k] = part.c_str()[0];
                line.erase(0, 1);
            }
        }

        //Get Mouse position
        input >> mouse.x >> mouse.y;

        //Get Cheese position
        int cheeseX, cheeseY;
        input >> cheeseX >> cheeseY;

        mazeArray[cheeseX][cheeseY] = '#';

        input.close();
    } // end if
} // end setupMaze
