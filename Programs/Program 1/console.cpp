/*
File       : console.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : September 21, 2015
Author     : Justin Kirk
Description: Main Driver. Handles Console output.
*/

#include <string>
#include <iostream>
#include <fstream>
#include "title.h"
#include "artist.h"
#include "year.h"
#include "binary.h"

//Prototypes

//Bulk
void checkBulkFile();

//Menu lists
void MainMenu();
void PrintMenu();
void DeleteMenu();
void ChangeRecordMenu();
void ChangeByArtistMenu();

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
void ChangeByTitleMenuInput();

//Used for InvalidInput
void LoadCurrentMenu();

//Print Menu functions
void PrintAll();
void PrintByArtist();
void PrintByTitle();
void PrintByYear();
void PrintSummary();

//Delete Menu Functions
void deleteByArtist();
void deleteByTitle();

//Change Menu Functions
void changeByArtist();
void changeByTitle(int selection);

//Other Menu Functions
void addARecord();
void sellATitle();
void soldValue();
void stopMenu();

//--End Prototypes

//Global Variables
int currentMenu = 0;
bool indexUpdated = false;

using namespace std;

int main(void)
{
    //Create Bulk if output.bin does not exist
    checkBulkFile();
    //Start the Main Menu
    //ArtistIndex art;
    //art.readSecondary();
    //art.writeSecondary();
    MainMenu();
    return 0;
}

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
        case(3): ChangeByArtistMenu();
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

//--------------------------------------------------//
//           cout Menu Functions
//--------------------------------------------------//

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
         << "  5  Print Summary" << endl
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

//The Change By Title print
void ChangeByArtistMenu()
{
    currentMenu = 3;
    ClearScreen();
    Header();
    cout << "  Change By Title" << endl << endl;
    cout << "  1  Quit" << endl
         << "  2  Submit" << endl
         << "  3  Title" << endl
         << "  4  Artist" << endl
         << "  5  Type" << endl
         << "  6  Year" << endl
         << "  7  Price" << endl
         << "  8  Count" << endl
         << "\n\n\n";
     ChangeByTitleMenuInput();
} // end MainMenu

//--------------------------------------------------//
//           Menu Selection Functions
//--------------------------------------------------//

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
            case('1'): stopMenu();
                     break;
            case('2'): PrintMenu();
                     break;
            case('3'): sellATitle();
                     break;
            case('4'): soldValue();
                     break;
            case('5'): addARecord();
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
            case('1'): PrintAll();
                     break;
            case('2'): PrintByTitle();
                     break;
            case('3'): PrintByArtist();
                     break;
            case('4'): PrintByYear();
                     break;
            case('5'): PrintSummary();
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
            case('1'): deleteByTitle();
                     break;
            case('2'): deleteByArtist();
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
            case('1'): changeByArtist();
                     break;
            case('2'): ChangeByArtistMenu();
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end ChangeRecordMenuInput

//Change By Title Menu Input selection
void ChangeByTitleMenuInput()
{
    string input;
    cout << "Please enter a selection from the Change By Title Menu (1-8): ";
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
            case('1'): changeByTitle(1);
                     break;
            case('2'): changeByTitle(2);
                     break;
            case('3'): changeByTitle(3);
                     break;
            case('4'): changeByTitle(4);
                     break;
            case('5'): changeByTitle(5);
                     break;
            case('6'): changeByTitle(6);
                     break;
            case('7'): changeByTitle(7);
                     break;
            case('8'): changeByTitle(8);
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end ChangeByTitleMenuInput


//--------------------------------------------------//
//           Print Menu Functions
//--------------------------------------------------//

//Print all records
void PrintAll()
{
    //Clear screen
    ClearScreen();
    char outputFileName[80] = "output.bin";
    //Read in file
    fstream outputFile(outputFileName, ios::in | ios::binary);

    int pos = 1;
    MyClass record;
    //std::cout << record.get_value(outputFile);
    if(outputFile.is_open())
    {
        record.readIt(outputFile, pos);
        while(!outputFile.eof())
        {
            if(!record.get_flag())
            {
                cout << "-----------" << endl;
                cout << " Record " << pos <<endl;
                cout << "-----------" << endl;
                cout << record;
            }
            pos++;
            record.readIt(outputFile, pos);
        }
        //Close file
        outputFile.close();
    }

    //Ask user to return -Ignores Invalid Input
	string input;
	cout << endl << endl << "Enter '1' to go back or '0' for Main Menu: ";
	cin >> input;

	if (input.size() > 1)
	{
		PrintMenu();
	} // end if
	else
	{
		const char* p_c_str = input.c_str();
		char inputChar = p_c_str[0];
		switch (inputChar)
		{
		case('0') : MainMenu();
			break;
		case('1') : PrintMenu();
			break;
		default: PrintMenu();
			break;
		} // end switch
	} // end else
} // End PrintAll

void PrintByTitle()
{
    cout << "PrintByTitle method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void PrintByArtist()
{
    cout << "PrintByArtist method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void PrintByYear()
{
    cout << "PrintByYear method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void PrintSummary()
{
    cout << "PrintSummary method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

//--------------------------------------------------//
//           Other Main Menu Functions
//--------------------------------------------------//

void stopMenu()
{
    if(indexUpdated)
    {
        char outputFileName[80] = "output.bin";
        //Read in file
        fstream outputFile(outputFileName, ios::in | ios::binary);

        int pos = 1;
        //Create binary object
        MyClass record;
        //Create Primary Index object
        PrimaryIndex primaryInx;
        //Create Secondary Index object
        ArtistIndex artistInx;
        YearIndex yearInx;

        if(outputFile.is_open())
        {
            record.readIt(outputFile, pos);
            while(!outputFile.eof())
            {
                if(!record.get_flag())
                {
                    //Pass Primary Key information to Primary Index(title, position)
                    primaryInx.set_title_key(record.get_title(), pos);

                    //Pass Secondary Key information to Secondary Index(artist or year, position)
                    artistInx.set_artist_key(record.get_artist(), pos);
                    yearInx.set_year_key(record.get_year(), pos);
                }
                pos++;
                record.readIt(outputFile, pos);
            } // end while

            //Write Primary Index to a file (open file using ofstream)
            primaryInx.writePrimary();
            //Write Secondary Index to a file (open file using ofstream)
            artistInx.writeSecondary();
            yearInx.writeSecondary();
            //Close file
            outputFile.close();
        } // end if
    } // end if indexUpdate

    cout << "Program stopped." << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    //Exit Program -Go back to main method
} // end stopMenu

void sellATitle()
{
    cout << "SellATitle method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void soldValue()
{
    cout << "soldValue method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void addARecord()
{
    cout << "addARecord method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}


//--------------------------------------------------//
//           Delete Menu Functions
//--------------------------------------------------//

void deleteByTitle()
{
    cout << "deleteByTitle method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void deleteByArtist()
{
    cout << "deleteByArtist method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

//--------------------------------------------------//
//           Change Record Menu Functions
//--------------------------------------------------//

void changeByArtist()
{
    cout << "changeByArtist method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void changeByTitle(int selection)
{
    //Quit
    if(selection == 1)
    {   //Go to Change By Menu
        currentMenu = 7;
        LoadCurrentMenu();
    }
    else //Everything else for now
    {
        cout << "changeByTitle method stubbed" << endl;
        string s;
        getline(cin, s);
        getline(cin, s);
        LoadCurrentMenu();
    }

}




