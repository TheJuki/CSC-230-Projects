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
            mazeArray[r][c]= '|';
        } // end for

    } // end for

    return 0;
}

void setupMaze(char mazeArray[][200])
{
 std::ifstream input("input.txt");
    int rowCount = 0;
    int columnCount = 0;
    input >> rowCount >> columnCount;

    if (input.is_open())
    {
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        size_t pos = 0;
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;

        while(!input.eof())
        {
            //Read in a line from the sequential file
            getline (input,line);

            //Defaults
            pos = 0;
            part = "";

            //Get MAZE
           for(int i = 0; i < columnCount; ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    ArtistIndex::my_list[position].pos[i] = atoi(part.c_str());
                    line.erase(0, pos + delimiter.length());
                }
            }
            //Get artist name
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                ArtistIndex::my_list[position].artist = part;
            }
            //Set pos to keys in line
            for(int i = 1; i < (numOfKeys + 1); ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    ArtistIndex::my_list[position].pos[i] = atoi(part.c_str());
                    line.erase(0, pos + delimiter.length());
                }
            }

            //position++
            position++;

        } // End eof while
        input.close();
    } // end if
} // end setupMaze
