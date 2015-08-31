/*
File       : console.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code console display
*/

#include <string>
#include <iostream>
#include <stdlib.h>

//Prototypes

//Menu lists
void MainMenu();
void PrintMenu();
void DeleteMenu();
void ChangeRecordMenu();

//Clearing and Invalid Selection Handling
void ClearScreen();
void InvalidInput();

//Header
void Header();

//Selection Input
void MainMenuInput();
void PrintMenuInput();
void DeleteMenuInput();
void ChangeRecordMenuInput();

//Used for InvalidInput
void LoadCurrentMenu();

//--End Prototypes

//Global Variables
int currentMenu = 0;

using namespace std;

//Lame way of clearing the console
void ClearScreen()
{
    cout << string( 100, '\n' );
} // end ClearScreen

void InvalidInput()
{
    string s;
    cout << "Invalid selection. Please try again.";
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
} // end InvalidInput

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
         << "\n\n";
} // end Header

//Load Current Menu
void LoadCurrentMenu()
{
     switch(currentMenu)
    {
        case(0): MainMenu();
                 break;
        case(1): ClearScreen();
                 break;
        case(2): PrintMenu();
                 break;
        case(3): ClearScreen();
                 break;
        case(4): ClearScreen();
                 break;
        case(5): ClearScreen();
                 break;
        case(6): DeleteMenu();
                 break;
        case(7): ChangeRecordMenu();
                 break;
        default: InvalidInput();
                 break;
    }
} // end LoadCurrentMenu

//The Main Menu print
void MainMenu()
{
    currentMenu = 0;
    ClearScreen();
    Header();
    cout << "  Main Menu" << endl << endl;
    cout << "  1  Stop" << endl
         << "  2  Print records" << endl
         << "  3  Sell a Title" << endl
         << "  4  Sold Value" << endl
         << "  5  Add a record" << endl
         << "  6  Delete a record" << endl
         << "  7  Change a record" << endl
         << "\n\n\n\n";
     MainMenuInput();
} // end MainMenu

//The Print Menu print
void PrintMenu()
{
    currentMenu = 2;
    ClearScreen();
    Header();
    cout << "  Print Menu" << endl << endl;
    cout << "  1  Print all" << endl
         << "  2  Print by Title" << endl
         << "  3  Print by Artist" << endl
         << "  4  Print by Year" << endl
         << "  5  Print by Summary" << endl
         << endl //6
         << endl //7
         << "\n\n\n\n";
     PrintMenuInput();
} // end PrintMenu

//The Delete Menu print
void DeleteMenu()
{
    currentMenu = 6;
    ClearScreen();
    Header();
    cout << "  Delete Menu" << endl << endl;
    cout << "  1  Delete a record by title" << endl
         << "  2  Delete a record by artist or year" << endl
         << endl //3
         << endl //4
         << endl //5
         << endl //6
         << endl //7
         << "\n\n\n\n";
     DeleteMenuInput();
} // end DeleteMenu

//The Change Record Menu print
void ChangeRecordMenu()
{
    currentMenu = 7;
    ClearScreen();
    Header();
    cout << "  Change Record Menu" << endl << endl;
    cout << "  1  Change by Artist/Year" << endl
         << "  2  Change By Title" << endl
         << endl //3
         << endl //4
         << endl //5
         << endl //6
         << endl //7
         << "\n\n\n\n";
     ChangeRecordMenuInput();
} // end ChangeRecordMenu



//Main Menu selection
void MainMenuInput()
{
    string input;
    cout << "Please enter a selection from the Main Menu (1-7): ";
    cin >> input;
    if(input.size() > 1)
    {
       InvalidInput();
    }
    else
    {
        const char* p_c_str = input.c_str();
        char inputChar = p_c_str[0];
        switch(inputChar)
        {
            case('1'): exit (0);
                     break;
            case('2'): PrintMenu();
                     break;
            case('3'): ClearScreen();
                     break;
            case('4'): ClearScreen();
                     break;
            case('5'): ClearScreen();
                     break;
            case('6'): DeleteMenu();
                     break;
            case('7'): ChangeRecordMenu();
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end MainMenuInput

//Print Menu selection
void PrintMenuInput()
{
    string input;
    cout << "Please make a selection (1-5) or type '0' to return: ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
    } // end if
    else
    {
        const char* p_c_str = input.c_str();
        char inputChar = p_c_str[0];
        switch(inputChar)
        {
            case('0'): MainMenu();
                     break;
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
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end PrintMenuInput

//Delete Menu selection
void DeleteMenuInput()
{
    string input;
    cout << "Please make a selection (1-2) or type '0' to return: ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
    } // end if
    else
    {
        const char* p_c_str = input.c_str();
        char inputChar = p_c_str[0];
        switch(inputChar)
        {
            case('0'): MainMenu();
                     break;
            case('1'): ClearScreen();
                     break;
            case('2'): ClearScreen();
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end DeleteMenuInput


//Change Record Menu selection
void ChangeRecordMenuInput()
{
    string input;
    cout << "Please make a selection (1-2) or type '0' to return: ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
    } // end if
    else
    {
        const char* p_c_str = input.c_str();
        char inputChar = p_c_str[0];
        switch(inputChar)
        {
            case('0'): MainMenu();
                     break;
            case('1'): ClearScreen();
                     break;
            case('2'): ClearScreen();
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end ChangeRecordMenuInput





