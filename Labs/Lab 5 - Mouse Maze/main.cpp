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
#include <cstdlib>

using namespace std;

void setupMaze(char mazeArray[][200]);
void stepUp(char mazeArray[][200]);
void stepDown(char mazeArray[][200]);
void stepRight(char mazeArray[][200]);
void stepLeft(char mazeArray[][200]);
void displayMaze(char mazeArray[][200]);

struct Mouse
{
    int x;
    int y;
} mouse;

std::ostream& operator<< (std::ostream &out, const Mouse &p)
{
    out << p.x << " " << p.y << std::endl;
    return out;
}

stack<Mouse> path;
int numActualCol;
int numActualRow;

int main()
{
    //stack<MINI> path;
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
    //cout << mazeArray[1][1] << endl;
    stepLeft(mazeArray);
    displayMaze(mazeArray);

    return 0;
} // end main

void stepUp(char mazeArray[][200])
{
    mouse = path.top();
    mazeArray[mouse.x][mouse.y] = 'M';
    mouse.x = mouse.x - 1;
    path.push(mouse);
    mazeArray[mouse.x][mouse.y] = '@';
}
void stepDown(char mazeArray[][200])
{
    mouse = path.top();
    mazeArray[mouse.x][mouse.y] = 'M';
    mouse.x = mouse.x + 1;
    path.push(mouse);
    mazeArray[mouse.x][mouse.y] = '@';
}
void stepRight(char mazeArray[][200])
{
    mouse = path.top();
    mazeArray[mouse.x][mouse.y] = 'M';
    mouse.y = mouse.y + 1;
    path.push(mouse);
    mazeArray[mouse.x][mouse.y] = '@';
}
void stepLeft(char mazeArray[][200])
{
    mouse = path.top();
    mazeArray[mouse.x][mouse.y] = 'M';
    mouse.y = mouse.y - 1;
    path.push(mouse);
    mazeArray[mouse.x][mouse.y] = '@';
}

void displayMaze(char mazeArray[][200])
{
    cout << endl;
     //Draw maze
        for(int i = 0; i < numActualRow; ++i)
        {
            cout << endl;
            for(int k = 0; k < numActualCol; ++k)
            {
                cout << mazeArray[i][k];
            }
        }
} // end displayMaze

void setupMaze(char mazeArray[][200])
{
    std::ifstream input("input.txt");

    if (input.is_open())
    {
        numActualCol = 0;
        numActualRow = 0;
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;
        //size of string
        size_t pos = 0;

        getline (input,line);
        //Get rows
        if ((pos = line.find(delimiter)) != std::string::npos)
        {
            part = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            numActualRow = atoi(part.c_str());
            numActualCol = atoi(line.c_str());
        }

        //Get MAZE
        for(int i = 0; i < numActualRow; ++i)
        {
            getline (input,line);

            for(int k = 0; k < numActualCol; ++k)
            {
                part = line.substr(0, 1);
                mazeArray[i][k] = part.c_str()[0];
                line.erase(0, 1);
            }
        }

        //Get Mouse position
        getline (input,line);
        //Get mouseX and mouseY
        if ((pos = line.find(delimiter)) != std::string::npos)
        {
            part = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            mouse.x = atoi(part.c_str());
            mouse.y = atoi(line.c_str());
            path.push(mouse);
        }

        //Get Cheese position
        getline (input,line);
        int cheeseX = 0;
        int cheeseY = 0;

        //Get cheeseX and cheeseY
        if ((pos = line.find(delimiter)) != std::string::npos)
        {
            part = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            cheeseX = atoi(part.c_str());
            cheeseY = atoi(line.c_str());
        }
        mazeArray[cheeseX][cheeseY] = '#';

        input.close();

        //Draw maze
        mazeArray[mouse.x][mouse.y] = '@';

        for(int i = 0; i < numActualRow; ++i)
        {
            cout << endl;
            for(int k = 0; k < numActualCol; ++k)
            {
                cout << mazeArray[i][k];
            }
        }
    } // end if
} // end setupMaze
