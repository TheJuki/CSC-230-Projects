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

//Global Variables
int currentMenu = 0;
bool indexUpdated = false;

enum recordMember {TITLE, ARTIST, TYPE, YEAR, PRICE, COUNT};
enum addChangeDelete {ADD_BY_TITLE, CHANGE_BY_TITLE, CHANGE_BY_ARTIST, CHANGE_BY_YEAR,
                        DELETE_BY_TITLE, DELETE_BY_ARTIST, DELETE_BY_YEAR};

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
void ChangeByArtistYearMenuInput();

//Used for InvalidInput
void LoadCurrentMenu();

//Used for Add / Delete / Change
void printTryAgain(addChangeDelete type);

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
bool confirmDelete();

//Change Menu Functions
void ChangeByArtistYearMenu();
void ChangeByTitleMenu();
void changeByTitle(int selection, MyClass& me);
void changeByArtistYear(recordMember member);

//Other Menu Functions
void addARecord();
void sellATitle();
void soldValue();
void stopMenu();

//Check for Dead Flags
bool checkDeadFlags(std::fstream& input, int& pos);

//--End Prototypes

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
        case(3): ChangeByTitleMenu();
                 break;
        case(4): ChangeByArtistYearMenu();
                 break;
        case(5): ChangeByTitleMenu();
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
void ChangeByArtistYearMenu()
{
    currentMenu = 4;
    ClearScreen();
    Header();
    cout << "  Change by Artist or Year" << endl << endl;
    cout << "  1  Change by Artist" << endl
         << "  2  Change by Year" << endl
         << endl //3
         << endl //4
         << endl //5
         << endl //6
         << endl //7
         << "\n\n\n\n";
     ChangeByArtistYearMenuInput();
} // end MainMenu

//The Change By Title print
void ChangeByTitleMenu()
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
            case('1'): ChangeByArtistYearMenu();
                     break;
            case('2'): ChangeByTitleMenu();
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end ChangeRecordMenuInput

//Change By Artist or Year Menu selection
void ChangeByArtistYearMenuInput()
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
            case('0'): ChangeRecordMenu();
                     break;
            case('1'): changeByArtistYear(ARTIST);
                     break;
            case('2'): changeByArtistYear(YEAR);
                     break;
            default: InvalidInput();
                     break;
        } // end switch
    } // end else
} // end ChangeByArtistYearMenuInput

//Change By Title Menu Input selection
void ChangeByTitleMenuInput()
{
    MyClass me;
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
            case('1'): changeByTitle(1, me);
                     break;
            case('2'): changeByTitle(2, me);
                     break;
            case('3'): changeByTitle(3, me);
                     break;
            case('4'): changeByTitle(4, me);
                     break;
            case('5'): changeByTitle(5, me);
                     break;
            case('6'): changeByTitle(6, me);
                     break;
            case('7'): changeByTitle(7, me);
                     break;
            case('8'): changeByTitle(8, me);
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

void printTryAgain(addChangeDelete type)
{
    //Ask user to return -Ignores Invalid Input
	string input;
	cout << endl << endl << " Enter '1' to try again or '0' to go back: ";
	cin >> input;

	if (input.size() > 1)
	{
		LoadCurrentMenu();
	} // end if
	else
	{
		const char* p_c_str = input.c_str();
		char inputChar = p_c_str[0];
		switch (type)
		{
		    case(ADD_BY_TITLE) :
                switch(inputChar)
                {
                    case('0') : LoadCurrentMenu();
                        break;
                    case('1') : addARecord();
                        break;
                    default: LoadCurrentMenu();
                        break;
                } // end switch ADD_BY_TITLE
                break;

            case(DELETE_BY_TITLE) :
                switch(inputChar)
                {
                    case('0') : LoadCurrentMenu();
                        break;
                    case('1') : deleteByTitle();
                        break;
                    default: LoadCurrentMenu();
                        break;
                } // end switch deleteByTitle
                break;
            default: LoadCurrentMenu();
                break;
		} // end switch type
	} // end else
}

//Print all records
void PrintAll()
{
    //Clear screen
    ClearScreen();
    Header();
    cout << " Display all records" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " All records are displayed." << endl
    << endl << endl;

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

    //Clear screen
    ClearScreen();
    Header();
    cout << " Display a record by title" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " Provide the title of the specific record to display."<< endl;
    cout << endl << endl << endl << endl;

    //Ask user
	string input;
	cout << endl << endl << " Enter the title to display record: ";
	cin >> input;

    //Find title
	int pos = 0;
	primaryInx->printTitle(input, pos);

	//If title found, then display it
	if(pos > 0)
    {
        char outputFileName[80] = "output.bin";
        //Read in file
        fstream file(outputFileName, ios::in | ios::binary);
        record.readIt(file, pos);
        if(!record.get_flag())
        {
            cout << endl << endl << " -INFORMATION-" << endl << endl;
            cout << " Here is the record for the title '"
                 << input << "'." << endl << endl << endl;
            cout << "-----------" << endl;
            cout << " Record " << pos <<endl;
            cout << "-----------" << endl;
            cout << record;
        } //  end if

        //Close file
        file.close();

        //Ask user to return a menu
        printReturn();
    } //end if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The title: '" << input << "' does not exist"
        << endl << endl << endl << endl;

        //Ask user to return a menu
        printReturn();
    }
}

void PrintByArtist()
{
    //Record
    MyClass record;

    //Secondary Index
    ArtistIndex artistInx;

    //Fill
    artistInx.readSecondary();

    //Clear screen
    ClearScreen();
    Header();
    cout << " Display records by artist" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " Provide the artist of records to display."<< endl;
    cout << " Up to 10 records with the provided artist will be displayed." << endl << endl << endl << endl;

    //Ask user
	string input;
	cout << endl << endl << " Enter a artist to display records: ";
	cin >> input;

    //Find artist
	int* pos = artistInx.findArtist(input);

	//If artist found, then display it
	if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " Here are the records for the artist '"
             << input << "'." << endl << endl << endl << endl;

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

        //Ask user to return a menu
        printReturn();
    } // End if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The artist: '" << input << "' does not exist"
        << endl << endl << endl;
        //Ask user to return a menu
        printReturn();
    }

}

void PrintByYear()
{
    //Record
    MyClass record;

    //Secondary Index
    YearIndex yearInx;

    //Fill
    yearInx.readSecondary();

    //Clear screen
    ClearScreen();
    Header();
    cout << " Display records by year" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " Provide the year of records to display."<< endl;
    cout << " Up to 10 records with the provided year will be displayed." << endl << endl << endl << endl;

   //Ask user
	string input;
	cout << endl << endl << " Enter a year to display records: ";
	cin >> input;

    //Find year
	int* pos = yearInx.findYear(atoi(input.c_str()));

	//If year found, then display it
	if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " Here are the records for the year '"
             << input << "'." << endl << endl << endl << endl;

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
        //Ask user to return a menu
        printReturn();
    } // End if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The year: '" << input << "' does not exist" << endl
        << endl << endl << endl;

        //Ask user to return a menu
        printReturn();
    }

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

    if(primaryInx->getMaxCount() != (MAX_LIMIT - 1))
       {
           //Provide general information
           cout << " -INFORMATION-" << endl << endl;
           cout <<  " To add a record, provide a new, non-existing title first."<< endl;
           cout << " Then provide the artist, type, year, price, and count." << endl << endl << endl << endl;

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
                cout << endl << endl << " -NOTICE-" << endl << endl;
                cout << " The record for the title: '"
                << input << "' already exists at index '" << pos << "'" << endl << endl << endl << endl;

                //Get user to try again
                printTryAgain(ADD_BY_TITLE);

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

                            int nextIndex = primaryInx->getMaxCount() + 1;

                            //Create a binary object
                            MyClass me(my_title, my_artist, my_type,
                               my_year, my_price, my_count);

                            //Check dead count
                            if(primaryInx->getDeadCount() > 0)
                            {
                                //Check for any available dead flag spot
                                if(!checkDeadFlags(outputFile, nextIndex))
                                {
                                     //Get number of records
                                     nextIndex = primaryInx->getMaxCount() + 1;
                                }
                                else
                                {
                                    primaryInx->setDeadCount(-1);
                                }
                            }

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
                            cout << endl << endl << " -INFORMATION-" << endl << endl;
                            cout <<  " The title: '" << my_title
                                 << "' was successfully added at index '" << nextIndex << "'."  << endl << endl << endl << endl;
                            //Ask user to return a menu
                            printReturn();
                        } // If Open
                        else
                        {
                            cout << endl << endl << " -NOTICE-" << endl << endl;
                            cout << endl <<  " The file could not be opened for writing." << endl << endl << endl << endl;
                            //Ask user to return a menu
                            printReturn();
                        } // Else Not Open
                   } // If Info filled in filled in correctly
                   else
                   {
                        cout << endl << endl << " -NOTICE-" << endl << endl;
                        cout << " The record for the title: '"
                        << my_title << "' has invalid fields." << endl;
                        cout << " Please make sure to fill in a valid value for each field." << endl;
                        cout << " Also, use '_' instead a spaces." << endl << endl << endl << endl;
                        //Get user to try again
                        printTryAgain(ADD_BY_TITLE);

                   } // Else Info not filled in correctly

            }// Else Title Not Found
       } //If Records not at limit
       else
       {
           //Provide error information
           cout << " -NOTICE-" << endl << endl;
           cout <<  " The max number of records '" << MAX_LIMIT - 1 << "' has been reached." << endl;
           cout << " Delete a record to add a new record." << endl << endl << endl << endl;

            //Ask user to return a menu
            printReturn();
       }
}


//--------------------------------------------------//
//           Delete Menu Functions
//--------------------------------------------------//

bool confirmDelete()
{
    //confirm boolean
    bool isYes = false;

    //Ask user to return -Ignores Invalid Input
	string input;
	cout << endl << endl << " Delete record (Y/N)? ";
	cin >> input;

	if (input.size() > 1)
	{
		isYes = false;
	} // end if
	else
	{
		const char* p_c_str = input.c_str();
		char inputChar = p_c_str[0];
		switch (inputChar)
		{
		case('Y') : isYes = true;
			break;
        case('y') : isYes = true;
            break;
		default: isYes = false;
			break;
		} // end switch
	} // end else

	return isYes;
}
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

    //Clear screen
    ClearScreen();
    Header();
    cout << " Deleting a new record" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " To delete a record, provide an existing title first."<< endl;
    cout << " Then confirm the deletion of the record." << endl << endl << endl << endl;

    //Ask user
	string input;
	cout << endl << endl << " Enter the title of the record for deletion: ";
	cin >> input;

    //Find title
	int pos = 0;
	primaryInx->matchTitle(input, pos);

    string my_title = "", my_artist = "";
    int my_year = 0;

	//If title found, delete it
	if(pos > 0)
    {
        my_title = input;
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " The record for the title: '" << my_title << "' can be deleted at index '" << pos << "'." << endl << endl << endl << endl;
        if(confirmDelete())
        {
             MyClass record;
            //Update Record (Dead)
            record.UpdateBinary(pos, my_artist, my_year);
            //Delete Title Index
            primaryInx->deleteTitle(my_title, pos);
            //Delete Artist Index
            artistInx.deleteArtist(my_artist, pos);
            //Delete Year Index
            yearInx.deleteYear(my_year, pos);

             //Write Indexes
            delete primaryInx;
            artistInx.writeSecondary();
            yearInx.writeSecondary();

            //Success!
            cout << endl << " -INFORMATION-" << endl << endl;
            cout <<  " Delete operation successful." << endl;
            cout << " The index: '" << pos << "' is now available." << endl;
            cout << " The record for the title: '" << my_title << "' was deleted." << endl << endl << endl << endl;

            //Ask user to return a menu
            printReturn();

        } // end if confirm
        else
        {
            cout << endl << " -INFORMATION-" << endl << endl;
            cout <<  " Delete operation canceled." << endl;
            cout << " No records were affected." << endl << endl << endl << endl;

            //Ask user to return a menu
            printReturn();
        }

    } //end if
    else // Title not found
    {
        cout << endl << " -NOTICE-" << endl << endl;
        cout <<  " Delete operation canceled."<< endl;
        cout << " No records were affected." << endl;
        cout << " The record for the title: '" << input << "' could not found for deletion." << endl << endl << endl << endl;

        //Ask user to try again
        printTryAgain(DELETE_BY_TITLE);
    }

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

void changeByArtistYear(recordMember member)
{
    cout << " changeByArtistYear method stubbed" << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
}

void changeByTitle(int selection, MyClass& me)
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

//--------------------------------------------------//
//           Check for a Dead Record slot
//--------------------------------------------------//
bool checkDeadFlags(fstream& input, int& pos)
{
    MyClass record;
    pos = 1;
    if(input.is_open())
    {
        record.readIt(input, pos);
        while(!input.eof())
        {
            if(record.get_flag())
            {
                //Dead record slot found
                return true;
            }
            pos++;
            record.readIt(input, pos);
        }
    }

    return false;
}
