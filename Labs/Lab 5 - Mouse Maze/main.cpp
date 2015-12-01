/*
File       : main.cpp
Program    : Lab 5 - Using Stacks for a mouse maze
Due Date   : December 1, 2015
Author     : Justin Kirk
             Breannah Parten
Description: A mouse in a char array mouse maze needs to find at least
             one piece of cheese.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cstdlib>

using namespace std;

//Prototypes
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

//Mouse
struct Mouse
{
    int x;
    int y;
} mouse;

//Output Mouse X and Y
std::ostream& operator<< (std::ostream &out, const Mouse &p)
{
    out << p.x << " " << p.y << std::endl;
    return out;
}

//ASSUMPTIONS:
/*
The Stack Class is included. The Stack pushes and pops the
struct Mouse (mouse) which contains both the X and Y ints.
This is most likely the best solution since both X and Y
are pushed or popped at the same time and are easy to obtain
when needed since the struct Mouse exists and be set to the
stack's top element.

*/
//Mouse path stack
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

    cout << endl << endl << " Initial mouse maze: ";
    setupMaze(mazeArray);
    string s;
    cout << endl << endl << " Mouse maze initialized. Press Enter to attempt a traversal... ";
    getline(cin, s);
    traverseMaze(mazeArray);

    return 0;
} // end main

// Move up one step
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

// Move down one step
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

// Move right one step
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

// Move left one step
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

// Move pop the stack until a new path is found
bool backTrackSteps(char mazeArray[][200])
{
    bool foundCheese = false;
    int currentX;
    int currentY;
    mouse = path.top();
    while(mazeArray[mouse.y][mouse.x] != '.' && path.size() > 1)
    {
        //Get current X and Y before pop
        currentX = mouse.x;
        currentY = mouse.y;

        foundCheese = false;

        //Set backtrack char
        mazeArray[mouse.y][mouse.x] = 'm';
        //Backtrack one
        path.pop();
        //Get new positions
        mouse = path.top();
        /*
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
        */
        bool hasStepped = false;
        std::size_t foundSpot;
        string spots = checkEmptySpot(mazeArray);

        foundSpot = spots.find("U");
        if(foundSpot!=std::string::npos)
        {
            foundCheese = stepUp(mazeArray);
            hasStepped = true;
        }
        foundSpot = spots.find("D");
        if(!foundCheese && !hasStepped && foundSpot!=std::string::npos)
        {

            foundCheese = stepDown(mazeArray);
            hasStepped = true;
        }
        foundSpot = spots.find("R");
        if(!foundCheese && !hasStepped && foundSpot!=std::string::npos)
        {

            foundCheese = stepRight(mazeArray);
            hasStepped = true;

        }
        foundSpot = spots.find("L");
        if(!foundCheese && !hasStepped && foundSpot!=std::string::npos)
        {

            foundCheese = stepLeft(mazeArray);
            hasStepped = true;

        }
        if(hasStepped)
            break;
        //Push backtrack
        // path.push(mouse);
        if(mazeArray[mouse.y][mouse.x] == '#')
            foundCheese = true;
        mazeArray[mouse.y][mouse.x] = '@';
        displayMaze(mazeArray);
       // string s;
         //cout << endl << endl << "Press Enter to Continue ";
         //getline(cin, s);
    }
    return foundCheese;
} // end backTrackSteps

//Display the current maze
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

//Return the walls surrounding the mouse
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
} // end checkWall

//Check for an empty spot
string checkEmptySpot(char mazeArray[][200])
{
    string spots = "";
    mouse = path.top();
    if (mazeArray[mouse.y + 1][mouse.x] == '.' || mazeArray[mouse.y + 1][mouse.x] == '#')
        spots += "D";
    if (mazeArray[mouse.y - 1][mouse.x] == '.' || mazeArray[mouse.y - 1][mouse.x] == '#')
        spots += "U";
    if (mazeArray[mouse.y][mouse.x + 1] == '.' || mazeArray[mouse.y][mouse.x + 1] == '#')
        spots += "R";
    if (mazeArray[mouse.y][mouse.x - 1] == '.' || mazeArray[mouse.y][mouse.x - 1] == '#')
        spots += "L";
    return spots;
} // end checkEmptySpot

//Check if a wall is detected
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
    case(' ') :
        return true;
    default :
        return false;
    }

    return false;
} // end isWall

//Check if mouse has visited a spot
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
} // end checkVisited

//Traverse the mouse maze while leaving "breadcrumbs" behind
void traverseMaze(char mazeArray[][200])
{
    int steps = 0;
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
        cout << endl << "Steps: " << steps << endl;
        // displayMaze(mazeArray);
        ++size;
        ++steps;
        // string s;
        // cout << endl << endl << "Press Enter to Continue ";
        // getline(cin, s);
    } // end while
    while(!foundCheese);
    if(foundCheese)
    {
        cout << endl << "Path: ";
        displayMaze(mazeArray);
        cout << endl << endl
             << "*****************************************************************" << endl
             << "*                          Found Cheese!                        *" << endl
             << "*****************************************************************" << endl;
        string s;
        cout << endl << endl << "Press Enter to Exit ";
        getline(cin, s);
    } // end if
} // end traverseMaze

//Get the maze, mouse, and pieces of cheese from input file
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
