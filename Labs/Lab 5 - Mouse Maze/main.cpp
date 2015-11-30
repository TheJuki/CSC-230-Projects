/*
File       : main.cpp
Program    : Lab 5 - Using Stacks for a mouse maze
Due Date   : October 30..., 2015
Author     : Justin Kirk
Description: A mouse in char array mouse maze needs to find at least
             one piece of cheese.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cstdlib>

using namespace std;

void setupMaze(char mazeArray[][200]);
bool stepUp(char mazeArray[][200]);
bool stepDown(char mazeArray[][200]);
bool stepRight(char mazeArray[][200]);
bool stepLeft(char mazeArray[][200]);
void displayMaze(char mazeArray[][200]);
string checkWall(char mazeArray[][200]);
void traverseMaze(char mazeArray[][200]);
string checkVisited(char mazeArray[][200]);
bool isWall(char wallChar);
string checkEmptySpot(char mazeArray[][200]);
bool backTrackSteps(char mazeArray[][200]);

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
    //200 rows
    int rows = 200;
    //200 columns
    int columns = 200;
    //Initialize array
    char mazeArray[200][200];
    //Current line
    string line = "";

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
    traverseMaze(mazeArray);

    return 0;
} // end main

bool stepUp(char mazeArray[][200])
{
    bool foundCheese = false;
    mouse = path.top();
    mazeArray[mouse.y][mouse.x] = 'M';
    mouse.y = mouse.y - 1;
    path.push(mouse);
    if(mazeArray[mouse.y][mouse.x] == '#')
        foundCheese = true;
    mazeArray[mouse.y][mouse.x] = '@';
    return foundCheese;
}
bool stepDown(char mazeArray[][200])
{
    bool foundCheese = false;
    mouse = path.top();
    mazeArray[mouse.y][mouse.x] = 'M';
    mouse.y = mouse.y + 1;
    path.push(mouse);
    if(mazeArray[mouse.y][mouse.x] == '#')
        foundCheese = true;
    mazeArray[mouse.y][mouse.x] = '@';
    return foundCheese;
}
bool stepRight(char mazeArray[][200])
{
    bool foundCheese = false;
    mouse = path.top();
    mazeArray[mouse.y][mouse.x] = 'M';
    mouse.x = mouse.x + 1;
    path.push(mouse);
    if(mazeArray[mouse.y][mouse.x] == '#')
        foundCheese = true;
    mazeArray[mouse.y][mouse.x] = '@';
    return foundCheese;
}
bool stepLeft(char mazeArray[][200])
{
    bool foundCheese = false;
    mouse = path.top();
    mazeArray[mouse.y][mouse.x] = 'M';
    mouse.x = mouse.x - 1;
    path.push(mouse);
    if(mazeArray[mouse.y][mouse.x] == '#')
        foundCheese = true;
    mazeArray[mouse.y][mouse.x] = '@';
    return foundCheese;
}

bool backTrackSteps(char mazeArray[][200])
{
    bool foundCheese = false;
    int currentX;
    int currentY;
    mouse = path.top();
    while(mazeArray[mouse.y][mouse.x] != '.')
    {
        //Get current X and Y before pop
        currentX = mouse.x;
        currentY = mouse.y;

        foundCheese = false;

        //Backtrack one
        path.pop();
        //Get new positions
        mouse = path.top();
        //Set backtrack char
        mazeArray[mouse.y][mouse.x] = 'm';

        //Step left
        if(currentX > mouse.x)
             mouse.x = mouse.x - 1;
        //Step right
        else if(currentX < mouse.x)
            mouse.x = mouse.x + 1;
        //Step up
        if(currentY > mouse.y)
             mouse.y = mouse.y - 1;
        //Step down
        else if(currentY < mouse.y)
            mouse.y = mouse.y + 1;

        //Push backtrack
        path.push(mouse);
        if(mazeArray[mouse.y][mouse.x] == '#')
            foundCheese = true;
        mazeArray[mouse.y][mouse.x] = '@';
        displayMaze(mazeArray);
    }
    return foundCheese;
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

string checkWall(char mazeArray[][200])
{
    string walls = "";
    mouse = path.top();
    if (isWall(mazeArray[mouse.y + 1][mouse.x]))
        walls += "D";
    if (isWall(mazeArray[mouse.y - 1][mouse.x]))
        walls += "U";
    if (isWall(mazeArray[mouse.y][mouse.x + 1]))
        walls += "R";
    if (isWall(mazeArray[mouse.y][mouse.x - 1]))
        walls += "L";
    return walls;
}

string checkEmptySpot(char mazeArray[][200])
{
    string spots = "";
    mouse = path.top();
    if (mazeArray[mouse.y + 1][mouse.x] == '.')
        spots += "D";
    if (mazeArray[mouse.y - 1][mouse.x] == '.')
        spots += "U";
    if (mazeArray[mouse.y][mouse.x + 1] == '.')
        spots += "R";
    if (mazeArray[mouse.y][mouse.x - 1] == '.')
        spots += "L";
    return spots;
}

bool isWall(char wallChar)
{
    switch(wallChar)
    {
         case('+') :
            return true;
         case('|') :
            return true;
         case('_') :
            return true;
         default :
            return false;
    }

    return false;
}

string checkVisited(char mazeArray[][200])
{
    string visted = "";
    mouse = path.top();
    if(mazeArray[mouse.y + 1][mouse.x] == 'M')
        visted += "DM";
    if(mazeArray[mouse.y - 1][mouse.x] == 'M')
        visted += "UM";
    if(mazeArray[mouse.y][mouse.x + 1] == 'M')
        visted += "RM";
    if(mazeArray[mouse.y][mouse.x - 1] == 'M')
        visted += "LM";
    return visted;
}

void traverseMaze(char mazeArray[][200])
{
    int size = 0;
    bool foundCheese = false;
    bool hasStepped = false;
    string walls = "";
    string visted = "";
    std::size_t foundWall;
    std::size_t foundVisted;
    do
    {
        hasStepped = false;
        walls = checkWall(mazeArray);
        visted = checkVisited(mazeArray);

        //found intersection
        if(walls.size() == 0)
        {
            foundVisted = visted.find("RM");
            if(foundVisted==std::string::npos)
            {
                foundCheese = stepRight(mazeArray);
                hasStepped = true;
            }
        }

        foundWall = walls.find("U");
        if(foundWall==std::string::npos)
        {
            foundVisted = visted.find("UM");
            if(foundVisted==std::string::npos)
            {
                foundCheese = stepUp(mazeArray);
                hasStepped = true;
            }
        }
        foundWall = walls.find("D");
        if(!foundCheese && !hasStepped && foundWall==std::string::npos)
        {
            foundVisted = visted.find("DM");
            if(foundVisted==std::string::npos)
            {
                foundCheese = stepDown(mazeArray);
                hasStepped = true;
            }
        }
        foundWall = walls.find("R");
        if(!foundCheese && !hasStepped && foundWall==std::string::npos)
        {
            foundVisted = visted.find("RM");
            if(foundVisted==std::string::npos)
            {
                foundCheese = stepRight(mazeArray);
                hasStepped = true;
            }
        }
        foundWall = walls.find("L");
        if(!foundCheese && !hasStepped && foundWall==std::string::npos)
        {
            foundVisted = visted.find("LM");
            if(foundVisted==std::string::npos)
            {
                foundCheese = stepLeft(mazeArray);
                hasStepped = true;
            }
        }

        //Backtrack
        if(!foundCheese && !hasStepped)
        {
            foundCheese = backTrackSteps(mazeArray);
        }

        displayMaze(mazeArray);
        ++size;
    }
    while(!foundCheese);
    if(foundCheese)
    {
         cout << endl << endl
         << "*****************************************************************" << endl
         << "*                          Found Cheese!                        *" << endl
         << "*****************************************************************" << endl;
        string s;
        cout << endl << endl << "Press Enter to Exit ";
        getline(cin, s);
    }
}

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
            mouse.y = atoi(part.c_str());
            mouse.x = atoi(line.c_str());
            path.push(mouse);
        }
        //Get Cheese Count
        int cheeseCount = 1;
        getline (input,line);
        cheeseCount =  atoi(line.c_str());
        //Get All cheese
         for(int i = 0; i < cheeseCount; ++i)
        {
            //Get Cheese position
            getline (input,line);
            int cheeseX = 0;
            int cheeseY = 0;

            //Get cheeseX and cheeseY
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                cheeseY = atoi(part.c_str());
                cheeseX = atoi(line.c_str());
            }
            mazeArray[cheeseY][cheeseX] = '#';
        } // end while

        input.close();

        //Draw maze
        mazeArray[mouse.y][mouse.x] = '@';

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
