/*
File       : main.cpp
Program    : Lab 4 -Detecting Hash Table Collisions
Due Date   : October 14, 2015
Author     : Justin Kirk
Description: Lab 4 uses 3 different formulas to hash titles into hash numbers
             and checks for collisions within each formula.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int Formula_1(std::string M);
int Formula_2(std::string M);
int Formula_3(std::string M);
std::string PadNumber(int num);
int MatchHash(int array[][3], int column, int numOfrows, int hash);

using namespace std;

int main()
{
    //73 rows
    int rows = 73;
    //3 columns
    int columns = 3;
    //Initialize array
    int array[73][3];
    //Current line
    string line = "";
    //current title
    string title = "";

    //Hash Numbers for each Formula
    int hash_num_1 = 0;
    int hash_num_2 = 0;
    int hash_num_3 = 0;

    //Counter for input row
    int counter = 0;

    //Number of collisions for each Formula
    int collsion_1 = 0;
    int collsion_2 = 0;
    int collsion_3 = 0;

    //Set all cells to 0
    for (int r = 0; r < rows; ++r)
    {
        line = "";
        for (int c = 0; c < columns; ++c)
        {
            array[r][c]= 0;
        } // end for

    } // end for

    //open file containing titles
    ifstream input("titles-fall15.txt");
    //check if file can be opened
    if(input.is_open())
    {
        cout << string(75, '-') << endl;
        cout << " Formula 1 | Formula 2 | Formula 3 | Title " << endl;
        cout << string(75, '-') << endl;
        do
        {
            //Get title
            input >> title;
            //Get 3 hash numbers
            hash_num_1 = Formula_1(title);
            hash_num_2 = Formula_2(title);
            hash_num_3 = Formula_3(title);

            //Get collisions
            collsion_1 += MatchHash(array, 0, counter, hash_num_1);
            collsion_2 += MatchHash(array, 1, counter, hash_num_2);
            collsion_3 += MatchHash(array, 2, counter, hash_num_3);

            //Set those 3 hash numbers in the array
            array[counter][0]= hash_num_1;
            array[counter][1]= hash_num_2;
            array[counter][2]= hash_num_3;

            //Create line to display
            line = "    ";
            line += PadNumber(array[counter][0]);
            line += string(9, 32);
            line += PadNumber(array[counter][1]);
            line += string(9, 32);
            line += PadNumber(array[counter][2]);
            line += string(6, 32);
            line += title;

            //Display line
            cout << line << endl;

            ++counter;

        }
        while(!input.eof() && counter != rows);

        //Display Collisions
        cout << string(75, '-') << endl;
        cout << " Collisions | Collisions | Collisions " << endl;
        cout << string(75, '-') << endl;

        line = "    ";
        line += PadNumber(collsion_1);
        line += string(9, 32);
        line += PadNumber(collsion_2);
        line += string(9, 32);
        line += PadNumber(collsion_3);
        line += string(6, 32);

        cout << line << endl;

        int highest = -1;
        if((collsion_1 == collsion_2) && (collsion_1 == collsion_3))
        {
            highest = -1;
        } // end if
        else
        {
            if(collsion_1 > collsion_2)
            {
                if(collsion_1 > collsion_3)
                {
                    highest = 1;
                }
                else if(collsion_1 == collsion_3)
                {
                    highest = 4;
                }
                else
                {
                    highest = 3;
                }
            } // end if
            else if((collsion_1 == collsion_2) && (collsion_1 > collsion_3))
            {
                highest = 0;
            }
            else
            {
                if(collsion_2 > collsion_3)
                {
                    highest = 2;
                }
                else if(collsion_2 == collsion_3)
                {
                    highest = 5;
                }
                else
                {
                    highest = 3;
                }
            } // end else
        } // end collisions not equal

        //Display highest collision formulas
        switch(highest)
        {
        case(-1):
            cout << string(75, '-') << endl;
            cout << "        All Formulas have equal collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(0):
            cout << string(75, '-') << endl;
            cout << "    Formula 1 and 2 have the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(1):
            cout << string(75, '-') << endl;
            cout << "        Formula 1 has the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(2):
            cout << string(75, '-') << endl;
            cout << "        Formula 2 has the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(3):
            cout << string(75, '-') << endl;
            cout << "        Formula 3 has the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(4):
            cout << string(75, '-') << endl;
            cout << "    Formula 1 and 3 have the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        case(5):
            cout << string(75, '-') << endl;
            cout << "    Formula 2 and 3 have the highest collisions " << endl;
            cout << string(75, '-') << endl;
            break;
        default : //Nothing
            break;
        }

        //Display Collisions
        input.close();
    } // end if file open

    //Wait for Enter
    cout << endl << endl << endl << endl << " Press Enter to Quit";
    string s;
    getline(cin, s);
    return 0;
}

//Formula 1 - Start at 1 and go up the length of M
int Formula_1(string M)
{
    int sum = 0;
    int length = M.length();
    int factor = 1;

    for (int i = 0; i < length; ++i)
    {
        sum += factor*M[i];
        ++factor;
    }

    return sum % 73;
}

//Formula 2 - Start at the length of M and go down to 1
int Formula_2(string M)
{
    int sum = 0;
    int length = M.length();
    int factor = length;

    for (int i = 0; i < length; ++i)
    {
        sum += factor*M[i];
        --factor;
    }

    return sum % 73;
}

//Formula 3 - Set factor to 2N+1
//Start at 1 and go up the length of M
int Formula_3(string M)
{
    int sum = 0;
    int factor = 0;
    int length = M.length();
    int N = 1;

    for (int i = 0; i < length; ++i)
    {
        factor = (2*N)+1;
        sum += factor*M[i];
        ++N;
    }

    return sum % 73;
}

//Attempt to pad numbers as ###
//Return the padded number as a string
string PadNumber(int num)
{
    //string stream for
    //int to string conversion
    stringstream strs;

    string padded_num;

    if(num < 10)
    {
        strs << num;
        padded_num = "  " + strs.str();
    }
    else if(num < 100)
    {
        strs << num;
        padded_num = " " + strs.str();
    }

    return padded_num;
}

//Find an existing hash number with the given column/formula
//Return 1 if one is found
int MatchHash(int array[][3], int column, int numOfrows, int hash)
{
    for (int i = 0; i < numOfrows; i++)
    {
        if(array[i][column] == hash)
        {
            //Found
            //cout <<  "Collision " << "Column: " << column << " Hash: "<< hash << endl;
            return 1;
        }
    } // end for

    return 0;
}
