/*
File       : console.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code console display
*/

#include <string>
#include <iostream>

//Prototypes
void MainMenu();
void ClearScreen();
void InvalidInput();
void Header();
void MainMenuInput();

using namespace std;

//Lame way of clearing the console
void ClearScreen()
{
    cout << string( 100, '\n' );
}

void InvalidInput()
{
    string s;
    cout << "Invalid selection. Please try again.";
    getline(cin, s);
    getline(cin, s);
    MainMenu();
}

//Header displayed on all menus
void Header()
{
    cout << "*****************************************************************" << endl
         << "*                          Art Gallery                          *" << endl
         << "*****************************************************************" << endl
         << "*                          Justin Kirk                          *" << endl
         << "*****************************************************************" << endl
         << "*                           Program 1                           *" << endl
         << "*****************************************************************" << endl
         << "\n\n\n\n";
}

//The Main Menu print
void MainMenu()
{
    ClearScreen();
    Header();
    cout << "  1  Stop" << endl
         << "  2  Print records" << endl
         << "  3  Sell a Title" << endl
         << "  4  Sold Value" << endl
         << "  5  Add a record" << endl
         << "  6  Delete a record" << endl
         << "  7  Change a record" << endl
         << "\n\n\n\n";
     MainMenuInput();
}

//The Print Menu print
void PrintMenu()
{
    ClearScreen();
    Header();
    cout << "  1  Print all" << endl
         << "  2  Print by Title" << endl
         << "  3  Print by Artist" << endl
         << "  4  Print by Year" << endl
         << "  5  Print by Summary" << endl
         << "\n\n\n\n";
     MainMenuInput();
}


//Main Menu selection
void MainMenuInput()
{
    char input;
    cout << "Please enter a selection from the Main Menu (1-7): ";
    cin >> input;

    switch(input)
    {
        case('1'): ClearScreen();
                 break;
        case('2'): ClearScreen();
                 break;
        case('3'): ClearScreen();
                 break;
        case('4'): ClearScreen();
                 break;
        case('5'): ClearScreen();
                 break;
        case('6'): ClearScreen();
                 break;
        case('7'): ClearScreen();
                 break;
        default: InvalidInput();
                 break;
    }
}

//Main Menu selection
void MainMenuInput()
{
    char input;
    cout << "Please enter a selection from the Main Menu (1-7): ";
    cin >> input;

    switch(input)
    {
        case('1'): ClearScreen();
                 break;
        case('2'): ClearScreen();
                 break;
        case('3'): ClearScreen();
                 break;
        case('4'): ClearScreen();
                 break;
        case('5'): ClearScreen();
                 break;
        case('6'): ClearScreen();
                 break;
        case('7'): ClearScreen();
                 break;
        default: InvalidInput();
                 break;
    }
}


