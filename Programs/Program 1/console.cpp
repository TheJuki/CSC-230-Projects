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
#include <stdlib.h>
#include "title.h"
#include "artist.h"
#include "year.h"
#include "binary.h"

//Prototypes

//Bulk
void checkBulkFile();

//Indexes
void fillIndexes();

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

//Used for Add / Delete / Change
void printTryAgain(char type);

//Print Menu functions
void printReturn();
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

//--End Global Variables

using namespace std;

//main
int main(void)
{
    //Create Bulk if output.bin does not exist
    checkBulkFile();
    //Start the Main Menu
    MainMenu();
    //Exit
    return 0;
}

//Lame way of clearing the console
void ClearScreen()
{
    cout << string(100, '\n');
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
    cout << " Please enter a selection from the Main Menu (1-7): ";
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
    cout << " Please make a selection (1-5) or type '0' to return: ";
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
    cout << " Please make a selection (1-2) or type '0' to return: ";
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
    cout << " Please make a selection (1-2) or type '0' to return: ";
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
    cout << " Please enter a selection from the Change By Title Menu (1-8): ";
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


void printReturn()
{
    //Ask user to return -Ignores Invalid Input
	string input;
	cout << endl << endl << " Enter '1' to go back or '0' for Main Menu: ";
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
		case('1') : LoadCurrentMenu();
			break;
		default: LoadCurrentMenu();
			break;
		} // end switch
	} // end else
}

void printTryAgain(char type)
{
    //Ask user to return -Ignores Invalid Input
	string input;
	cout << endl << endl << " Enter '1' to try again or '0' to go back: ";
	cin >> input;

	if (input.size() > 1)
	{
		PrintMenu();
	} // end if
	else
	{
		const char* p_c_str = input.c_str();
		char inputChar = p_c_str[0];
		if(type == 'A')
        {
            switch (inputChar)
            {
            case('0') : LoadCurrentMenu();
                break;
            case('1') : addARecord();
                break;
            default: LoadCurrentMenu();
                break;
            } // end switch
        }

	} // end else
}

//Print all records
void PrintAll()
{
    //Clear screen
    ClearScreen();
    char outputFileName[80] = "output.bin";
    //Read in file
    fstream file(outputFileName, ios::in | ios::binary);

    int pos = 1;
    MyClass record;
    //std::cout << record.get_value(file);
    if(file.is_open())
    {
        record.readIt(file, pos);
        while(!file.eof())
        {
            if(!record.get_flag())
            {
                cout << "-----------" << endl;
                cout << " Record " << pos <<endl;
                cout << "-----------" << endl;
                cout << record;
            }
            pos++;
            record.readIt(file, pos);
        }
        //Close file
        file.close();
    }

    //Ask user to return a menu
    printReturn();

} // End PrintAll

void PrintByTitle()
{
    //Record
    MyClass record;

     //Primary Indexes
    Primary* primaryInx = new Primary(0);

    //Secondary Indexes
    ArtistIndex artistInx;
    YearIndex yearInx;

    //Ask user
	string input;
	cout << endl << endl << " Enter the title to display record: ";
	cin >> input;

    //Find title
	int pos = 0;
	primaryInx->printTitle(input, pos);

    //Clear screen
    ClearScreen();

	//If title found, then display it
	if(pos > 0)
    {
        char outputFileName[80] = "output.bin";
        //Read in file
        fstream file(outputFileName, ios::in | ios::binary);
        record.readIt(file, pos);
        if(!record.get_flag())
        {
            cout << " Here is the record for the title '"
                 << input << "'." << endl << endl;
            cout << "-----------" << endl;
            cout << " Record " << pos <<endl;
            cout << "-----------" << endl;
            cout << record;
        } //  end if

        //Close file
        file.close();
    } //end if
    else // Title not found
    {
        cout << " The title: '" << input << "' does not exist" << endl;
    }

    //Ask user to return a menu
    printReturn();
}

void PrintByArtist()
{
    //Record
    MyClass record;

    //Secondary Index
    ArtistIndex artistInx;

    //Fill
    artistInx.readSecondary();


    //Ask user
	string input;
	cout << endl << endl << " Enter a artist to display records: ";
	cin >> input;

    //Find artist
	int* pos = artistInx.findArtist(input);

    //Clear screen
    ClearScreen();

	//If artist found, then display it
	if(*pos > 0)
    {
        cout << " Here are the records for the artist '"
             << input << "'." << endl << endl;

        char outputFileName[80] = "output.bin";
        //Read in file
        fstream file(outputFileName, ios::in | ios::binary);

        for(int i = 1; i < (*pos + 1); i++)
        {
            record.readIt(file, *(pos + i));
            if(!record.get_flag())
            {
                cout << "-----------" << endl;
                cout << " Record " << *(pos + i) <<endl;
                cout << "-----------" << endl;
                cout << record;
            } // End if
        } // end for

        //Close file
        file.close();
    } // End if
    else // Title not found
    {
        cout << " The artist: '" << input << "' does not exist" << endl;
    }

    //Ask user to return a menu
    printReturn();
}

void PrintByYear()
{
    //Record
    MyClass record;

    //Secondary Index
    YearIndex yearInx;

    //Fill
    yearInx.readSecondary();

   //Ask user
	string input;
	cout << endl << endl << " Enter a year to display records: ";
	cin >> input;

    //Find year
	int* pos = yearInx.findYear(atoi(input.c_str()));

    //Clear screen
    ClearScreen();

	//If year found, then display it
	if(*pos > 0)
    {
        cout << " Here are the records for the year '"
             << input << "'." << endl << endl;

        char outputFileName[80] = "output.bin";
        //Read in file
        fstream file(outputFileName, ios::in | ios::binary);

        for(int i = 1; i < (*pos + 1); i++)
        {
            record.readIt(file, *(pos + i));
            if(!record.get_flag())
            {
                cout << "-----------" << endl;
                cout << " Record " << *(pos + i) <<endl;
                cout << "-----------" << endl;
                cout << record;
            } // End if
        } // end for

        //Close file
        file.close();
    } // End if
    else // Title not found
    {
        cout << " The year: '" << input << "' does not exist" << endl;
    }

    //Ask user to return a menu
    printReturn();
}

void PrintSummary()
{
    cout << " PrintSummary method stubbed" << endl;
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
        Primary* primaryInx = new Primary();
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
                     primaryInx->addTitle(record.get_title(), pos);

                    //Pass Secondary Key information to Secondary Index(artist or year, position)
                    artistInx.set_artist_key(record.get_artist(), pos);
                    yearInx.set_year_key(record.get_year(), pos);
                }
                pos++;
                record.readIt(outputFile, pos);
            } // end while

            //Write Primary Index to a file (open file using ofstream)
            delete primaryInx;
            //Write Secondary Index to a file (open file using ofstream)
            artistInx.writeSecondary();
            yearInx.writeSecondary();
            //Close file
            outputFile.close();
        } // end if
    } // end if indexUpdate

    cout << " Program stopped." << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    //Exit Program -Go back to main method
} // end stopMenu

void sellATitle()
{
    cout << " SellATitle method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void soldValue()
{
    cout << " soldValue method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void addARecord()
{
    //Record
    MyClass record;

     //Primary Indexes
    Primary* primaryInx = new Primary(0);

    //Secondary Indexes
    ArtistIndex artistInx;
    YearIndex yearInx;

    //Fill
    artistInx.readSecondary();
    yearInx.readSecondary();

    //Clear screen
    ClearScreen();
    Header();
    cout << " Adding a new record" << endl
         << endl  << endl  << endl;

    //Ask user
	string input;
	cout << endl << endl << " Enter the title for the new record: ";
	cin >> input;

    //Find title
	int pos = 0;
	primaryInx->matchTitle(input, pos);

    string my_title = "", my_artist = "", my_type = "";
    int my_year = 0, my_price = 0, my_count = 0;

	//If title found, then throw an error
	if(pos > 0)
    {
        cout << endl << " The record for the title: '"
        << input << "' already exists at index '" << pos << "'" << endl;

        //Get user to try again
        printTryAgain('A');

    } //end if
    else // Title not found
    {
        my_title = input;

        cout << endl << " Provide the rest of information for the title: '" << input << "'" << endl;

        //Rest of the information
        cout << endl << " Artist name: ";
        cin >> input;
        my_artist = input;

        cout << endl <<  " Type of work: ";
        cin >> input;
        my_type = input;

        cout << endl <<  " Year produced: ";
        cin >> input;
        my_year = atoi(input.c_str());

        cout << endl <<  " Price: ";
        cin >> input;
        my_price = atoi(input.c_str());

        cout << endl <<  " Count: ";
        cin >> input;
        my_count = atoi(input.c_str());

        if(my_artist != "" && my_title != "" &&  my_type != ""
           && my_count >= 0 && my_year > 0 && my_price >= 0)
           {
                char outputFileName[80] = "output.bin";
                //Open Binary file for binary|writing using fstream
                //ios::in | ios::out | ios::binary used for adding/changing
                fstream outputFile(outputFileName, ios::in | ios::out | ios::binary);
                //Check to see if file is open
                if(outputFile.is_open())
                {
                    //Get number of records
                    int nextIndex = primaryInx->getMaxCount() + 1;
                    cout << " Number of Records: " << nextIndex << endl;

                    //Create a binary object
                    MyClass me(my_title, my_artist, my_type,
                       my_year, my_price, my_count);

                    //Write the binary file
                    me.writeIt(outputFile, nextIndex);

                    //Close file
                    outputFile.close();

                    //Add Indexes
                    primaryInx->addTitle(my_title, nextIndex);
                    artistInx.set_artist_key(my_artist, nextIndex);
                    yearInx.set_year_key(my_year, nextIndex);

                    //Write Indexes
                    delete primaryInx;
                    artistInx.writeSecondary();
                    yearInx.writeSecondary();

                    //Success!
                    cout << endl <<  " The title: '" << my_title
                         << "' was successfully added at index '" << nextIndex << "'" << endl;
                } // If Open
                else
                {
                    cout << endl <<  " The file could not be opened for writing." << endl;
                } // Else Not Open
           } // If Info filled in filled in correctly
           else
           {
                cout << endl << " The record for the title: '"
                << my_title << "' has invalid fields." << endl;

                cout << " Please make sure to fill in a valid value for each field." << endl;
                cout << " Also, use '_' instead a spaces." << endl;
                //Get user to try again
                printTryAgain('A');

           } // Else Info not filled in correctly

    } // Else Title Not Found

    //Ask user to return a menu
    printReturn();
}


//--------------------------------------------------//
//           Delete Menu Functions
//--------------------------------------------------//

void deleteByTitle()
{
   //Record
    MyClass record;

     //Primary Indexes
    Primary* primaryInx = new Primary(0);

    //Secondary Indexes
    ArtistIndex artistInx;
    YearIndex yearInx;

    //Fill
    artistInx.readSecondary();
    yearInx.readSecondary();

    //Ask user
	string input;
	cout << endl << endl << " Enter the title of the record for deletion: ";
	cin >> input;

    //Find title
	int pos = 0;
	primaryInx->matchTitle(input, pos);

    //Clear screen
    ClearScreen();

    string my_title = "", my_artist = "", my_type = "";
    int my_year = 0, my_price = 0, my_count = 0;

	//If title found, delete it
	if(pos > 0)
    {
        cout << " The title: '" << input << "' already exists at index '" << pos << "'" << endl;
    } //end if
    else // Title not found
    {
        cout << " The record for the title: '" << input << "' could not found for deletion." << endl;
    }

    printReturn();

}

void deleteByArtist()
{
    cout << " deleteByArtist method stubbed" << endl;
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
    cout << " changeByArtist method stubbed" << endl;
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
        cout << " changeByTitle method stubbed" << endl;
        string s;
        getline(cin, s);
        getline(cin, s);
        LoadCurrentMenu();
    }

}
