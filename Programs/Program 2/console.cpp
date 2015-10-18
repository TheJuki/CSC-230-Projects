/*
File       : console.cpp
Program    : Program 2 - Dynamic Array Indexes
Due Date   : October 12, 2015
Author     : Justin Kirk
Description: Main Driver. Handles Console output.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "title.h"
#include "artist.h"
#include "year.h"
#include "binary.h"


//--Global Variables

int currentMenu = 0;
bool flag_titleChanged = false;
bool flag_artistChanged = false;
bool flag_yearChanged = false;

//Global Index Objects
TitleIndex * primaryInx;
ArtistIndex * artistInx;
YearIndex * yearInx;

enum recordMember {TITLE, ARTIST, TYPE, YEAR, PRICE, COUNT};
enum addChangeDelete {ADD_BY_TITLE, CHANGE_BY_TITLE, CHANGE_BY_ARTIST, CHANGE_BY_YEAR,
                      DELETE_BY_TITLE, DELETE_BY_ARTIST, DELETE_BY_YEAR, SELL
                     };

//--End Global Variables


//--Prototypes

//Bulk
void CheckBulkFile();

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
void ChangeByTitleMenuInput(MyClass& me, const int position);
void ChangeByArtistYearMenuInput();

//Used for InvalidInput
void LoadCurrentMenu();

//Used for Add / Delete / Change / Sell
void PrintTryAgain(addChangeDelete type);

//Print Menu functions
void printReturn();
void PrintAll();
void PrintByArtist();
void PrintByTitle();
void PrintByYear();
void PrintSummary();

//Delete Menu Functions
void DeleteByArtistYear(recordMember member);
void DeleteByTitle();
bool ConfirmDelete();
void DeleteRecord(std::fstream& file, const int& pos);

//Change Menu Functions
void ChangeByArtistYearMenu();
void ChangeByTitleMenu(MyClass& me, const int position);
void ChangeByTitle(int selection, MyClass& me, const int position);
void ChangeByTitlePreMenu();
void ChangeByArtistYear(recordMember member);

//Other Menu Functions
void AddRecord();
void SellTitle();
void SoldValue();
void StopMenu();

//Check for Dead Flags
bool CheckDeadFlags(std::fstream& input, int& pos);

//--End Prototypes

using namespace std;

//--------------------------------------------------//
//  Check for Binary, load indexes, start Main Menu
//--------------------------------------------------//
int main(void)
{
    //Create Bulk if output.bin does not exist
    CheckBulkFile();

    //Read in Indexes
    primaryInx = new TitleIndex(0);
    artistInx = new ArtistIndex(0);
    yearInx = new YearIndex(0);

    //Start the Main Menu
    MainMenu();
    //Exit
    return 0;
}

//--------------------------------------------------//
//      Add 100 lines to "clear" the console
//--------------------------------------------------//
void ClearScreen()
{
    cout << string(100, '\n');
} // end ClearScreen

//--------------------------------------------------//
// Print Invalid selection and call LoadCurrentMenu
//--------------------------------------------------//
void InvalidInput()
{
    string s;
    cout << "Invalid selection. Please try again.";
    getline(cin, s);
    getline(cin, s);
    LoadCurrentMenu();
} // end InvalidInput

//--------------------------------------------------//
//                  Print Header
//--------------------------------------------------//
void Header()
{
    cout << "*****************************************************************" << endl
         << "*                          Art Gallery                          *" << endl
         << "*****************************************************************" << endl
         << "*                          Justin Kirk                          *" << endl
         << "*****************************************************************" << endl
         << "*                           Program 2                           *" << endl
         << "*****************************************************************" << endl
         << "\n\n";
} // end Header

//--------------------------------------------------//
//       Call current Print Menu function
//--------------------------------------------------//
void LoadCurrentMenu()
{
    switch(currentMenu)
    {
    case(0):
        MainMenu();
        break;
    case(1):
        ClearScreen();
        break;
    case(2):
        PrintMenu();
        break;
    case(3):
        //Just Break and Return
        break;
    case(4):
        ChangeRecordMenu();
        break;
    case(5):
        ChangeByTitlePreMenu();
        break;
    case(6):
        DeleteMenu();
        break;
    case(7):
        ChangeRecordMenu();
        break;
    case(8):
        MainMenu();
        break;
    default:
        InvalidInput();
        break;
    }
} // end LoadCurrentMenu

//--------------------------------------------------//
//              Print Menu Functions
//--------------------------------------------------//


//--------------------------------------------------//
//          Print Main Menu
//--------------------------------------------------//
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

//--------------------------------------------------//
//          Print 'Print' Menu
//--------------------------------------------------//
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

//--------------------------------------------------//
//          Print Delete Menu
//--------------------------------------------------//
void DeleteMenu()
{
    currentMenu = 6;
    ClearScreen();
    Header();
    cout << "  Delete Menu" << endl << endl;
    cout << "  1  Delete a record by Title" << endl
         << "  2  Delete a record by Artist" << endl
         << "  3  Delete a record by Year" << endl
         << endl //4
         << endl //5
         << endl //6
         << endl //7
         << "\n\n\n\n";
    DeleteMenuInput();
} // end DeleteMenu

//--------------------------------------------------//
//          Print Change Record Menu
//--------------------------------------------------//
void ChangeRecordMenu()
{
    currentMenu = 7;
    ClearScreen();
    Header();
    cout << "  Change Record Menu" << endl << endl;
    cout << "  1  Change by Title" << endl
         << "  2  Change by Artist" << endl
         << "  3  Change By Year" << endl
         << endl //3
         << endl //4
         << endl //5
         << endl //6
         << endl //7
         << "\n\n\n\n";
    ChangeRecordMenuInput();
} // end ChangeRecordMenu

//--------------------------------------------------//
//          Print Change By Title Menu
//--------------------------------------------------//
void ChangeByTitleMenu(MyClass& me, int position)
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
    ChangeByTitleMenuInput(me, position);
} // end MainMenu

//--------------------------------------------------//
//           Menu Selection Functions
//--------------------------------------------------//


//--------------------------------------------------//
//            Main Menu Selection
//--------------------------------------------------//
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
        char inputChar = input[0];
        switch(inputChar)
        {
        case('1'):
            StopMenu();
            break;
        case('2'):
            PrintMenu();
            break;
        case('3'):
            SellTitle();
            break;
        case('4'):
            SoldValue();
            break;
        case('5'):
            AddRecord();
            break;
        case('6'):
            DeleteMenu();
            break;
        case('7'):
            ChangeRecordMenu();
            break;
        default:
            InvalidInput();
            break;
        } // end switch
    } // end else
} // end MainMenuInput

//--------------------------------------------------//
//            Print Menu Selection
//--------------------------------------------------//
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
        char inputChar = input[0];
        switch(inputChar)
        {
        case('0'):
            MainMenu();
            break;
        case('1'):
            PrintAll();
            break;
        case('2'):
            PrintByTitle();
            break;
        case('3'):
            PrintByArtist();
            break;
        case('4'):
            PrintByYear();
            break;
        case('5'):
            PrintSummary();
            break;
        default:
            InvalidInput();
            break;
        } // end switch
    } // end else
} // end PrintMenuInput

//--------------------------------------------------//
//            Delete Menu Selection
//--------------------------------------------------//
void DeleteMenuInput()
{
    string input;
    cout << " Please make a selection (1-3) or type '0' to return: ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
    } // end if
    else
    {
        char inputChar = input[0];
        switch(inputChar)
        {
        case('0'):
            MainMenu();
            break;
        case('1'):
            DeleteByTitle();
            break;
        case('2'):
            DeleteByArtistYear(ARTIST);
            break;
        case('3'):
            DeleteByArtistYear(YEAR);
            break;
        default:
            InvalidInput();
            break;
        } // end switch
    } // end else
} // end DeleteMenuInput


//--------------------------------------------------//
//           Change Record Menu Selection
//--------------------------------------------------//
void ChangeRecordMenuInput()
{
    string input;
    cout << " Please make a selection (1-3) or type '0' to return: ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
    } // end if
    else
    {
        char inputChar = input[0];
        switch(inputChar)
        {
        case('0'):
            MainMenu();
            break;
        case('1'):
            ChangeByTitlePreMenu();
            break;
        case('2'):
            ChangeByArtistYear(ARTIST);
            break;
        case('3'):
            ChangeByArtistYear(YEAR);
            break;
        default:
            InvalidInput();
            break;
        } // end switch
    } // end else
} // end ChangeRecordMenuInput

//--------------------------------------------------//
//          Change By Title Menu Selection
//--------------------------------------------------//
void ChangeByTitleMenuInput(MyClass& me, int position)
{
    string input;
    cout << " Please enter a selection from the Change By Title Menu (1-8): ";
    cin >> input;
    if(input.size() > 1)
    {
        InvalidInput();
        ChangeByTitleMenu(me, position);
    }
    else
    {
        char inputChar = input[0];
        switch(inputChar)
        {
        case('1'):
            ChangeByTitle(1, me, position);
            break;
        case('2'):
            ChangeByTitle(2, me, position);
            break;
        case('3'):
            ChangeByTitle(3, me, position);
            break;
        case('4'):
            ChangeByTitle(4, me, position);
            break;
        case('5'):
            ChangeByTitle(5, me, position);
            break;
        case('6'):
            ChangeByTitle(6, me, position);
            break;
        case('7'):
            ChangeByTitle(7, me, position);
            break;
        case('8'):
            ChangeByTitle(8, me, position);
            break;
        default:
            InvalidInput();
            ChangeByTitleMenu(me, position);
            break;
        } // end switch
    } // end else
} // end ChangeByTitleMenuInput


//--------------------------------------------------//
//           Print Menu Functions
//--------------------------------------------------//


//--------------------------------------------------//
//   Ask to return to previous menu or Main Menu
//--------------------------------------------------//
void PrintReturn()
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
        char inputChar = input[0];
        switch (inputChar)
        {
        case('0') :
            MainMenu();
            break;
        case('1') :
            LoadCurrentMenu();
            break;
        default:
            LoadCurrentMenu();
            break;
        } // end switch
    } // end else
} // end printReturn

//--------------------------------------------------//
//  Display a try again message and return to a menu
//--------------------------------------------------//
void PrintTryAgain(addChangeDelete type)
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
        char inputChar = input[0];
        switch (type)
        {
        case(ADD_BY_TITLE) :
            switch(inputChar)
            {
            case('1') :
                AddRecord();
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch ADD_BY_TITLE
            break;

        case(DELETE_BY_TITLE) :
            switch(inputChar)
            {
            case('1') :
                DeleteByTitle();
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch DELETE_BY_TITLE
            break;
        case(CHANGE_BY_TITLE) :
            switch(inputChar)
            {
            case('1') :
                ChangeByTitlePreMenu();
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch CHANGE_BY_ARTIST
            break;
        case(CHANGE_BY_ARTIST) :
            switch(inputChar)
            {
            case('1') :
                ChangeByArtistYear(ARTIST);
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch CHANGE_BY_ARTIST
            break;
        case(CHANGE_BY_YEAR) :
            switch(inputChar)
            {
            case('1') :
                ChangeByArtistYear(YEAR);
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch CHANGE_BY_YEAR
            break;
        case(SELL) :
            switch(inputChar)
            {
            case('1') :
                SellTitle();
                break;
            default:
                LoadCurrentMenu();
                break;
            } // end switch CHANGE_BY_YEAR
            break;
        default:
            LoadCurrentMenu();
            break;
        } // end switch type
    } // end else
} // end printTryAgain

//--------------------------------------------------//
//               Display all records
//--------------------------------------------------//
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

    //Read in file
    fstream file("output.bin", ios::in | ios::binary);

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
    } // if file is open
    else
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The file for reading does not exist" << endl << endl << endl << endl;
    } // end file not open

    //Ask user to return a menu
    PrintReturn();

} // End PrintAll

//--------------------------------------------------//
//       Display all records with given title
//--------------------------------------------------//
void PrintByTitle()
{
    //Record
    MyClass record;

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
        //Read in file
        fstream file("output.bin", ios::in | ios::binary);
        if(file.is_open())
        {
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

        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open

    } //end if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The title: '" << input << "' does not exist"
             << endl << endl << endl << endl;
    }
    //Ask user to return a menu
    PrintReturn();
} // end PrintByTitle

//--------------------------------------------------//
//       Display all records with given artist
//--------------------------------------------------//
void PrintByArtist()
{
    //Record
    MyClass record;

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
    int* pos = artistInx->findArtist(input);

    //If artist found, then display it
    if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " Here are the records for the artist '"
             << input << "'." << endl << endl << endl << endl;

        //Read in file
        fstream file("output.bin", ios::in | ios::binary);

        if(file.is_open())
        {
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
        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open

    } // End if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The artist: '" << input << "' does not exist"
             << endl << endl << endl;
    }
    //Ask user to return a menu
    PrintReturn();
} // end PrintByArtist

//--------------------------------------------------//
//       Display all records with given year
//--------------------------------------------------//
void PrintByYear()
{
    //Record
    MyClass record;

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
    int* pos = yearInx->findYear(atoi(input.c_str()));

    //If year found, then display it
    if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " Here are the records for the year '"
             << input << "'." << endl << endl << endl << endl;

        //Read in file
        fstream file( "output.bin", ios::in | ios::binary);

        if(file.is_open())
        {
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

        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open
    } // End if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The year: '" << input << "' does not exist" << endl
             << endl << endl << endl;


    }
    //Ask user to return a menu
    PrintReturn();
} // end PrintByYear

//--------------------------------------------------//
// Display a summary (average price and average sold)
//--------------------------------------------------//
void PrintSummary()
{
    //Clear screen
    ClearScreen();
    Header();
    cout << " Summary" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " The average price and average sold are displayed." << endl
         << endl << endl;

    fstream file("output.bin", ios::in | ios::binary);

    int pos = 1;

    int total_items = 0;
    int total_price = 0;
    MyClass record;
    //std::cout << record.get_value(file);
    if(file.is_open())
    {
        record.readIt(file, pos);
        while(!file.eof())
        {
            if(!record.get_flag())
            {
                total_price += record.get_price() * record.get_count();
                total_items += record.get_count();
            }
            pos++;
            record.readIt(file, pos);
        } // end while

        //Close file
        file.close();
        //Reopen file
        file.open("output.bin", ios::in | ios::binary);

        //Read zero record
        record.get_value(file);

        //Average Price
        if(total_items == 0)
        {
            cout << "--------------------------" << endl;
            cout << " Average Price: $" << 0 << endl;
            cout << "--------------------------" << endl;
        }
        else
        {
            cout << "--------------------------" << endl;
            cout << " Average Price: $" << total_price / total_items << endl;
            cout << "--------------------------" << endl;
        }

        //Average Sold Value
        if(record.get_count() == 0)
        {
            cout << "--------------------------" << endl;
            cout << " Average sold: $" << 0 << endl;
            cout << "--------------------------" << endl;
        }
        else
        {
            cout << "--------------------------" << endl;
            cout << " Average sold: $" << record.get_price() / record.get_count() << endl;
            cout << "--------------------------" << endl;
        }
        //Dead Count
        cout << "--------------------------" << endl;
        cout << " Deleted records: " << primaryInx->getDeadCount() << endl;
        cout << "--------------------------" << endl << endl << endl;

    } // if file is open
    else
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The file for reading does not exist" << endl << endl << endl << endl;
    } // end file not open

    //Ask user to return a menu
    PrintReturn();
} // end printSummary

//--------------------------------------------------//
//           Other Main Menu Functions
//--------------------------------------------------//


//--------------------------------------------------//
//         Delete (Write) Indexes and Quit
//--------------------------------------------------//
void StopMenu()
{
    //Write out indexes
    //Delete Index object pointers
    delete artistInx;
    delete primaryInx;
    delete yearInx;

    cout << " Program stopped." << endl;
    string s;
    getline(cin, s);
    getline(cin, s);
    //Exit Program -Go back to main method
} // end stopMenu

//--------------------------------------------------//
//  Get the number of items sold for a given title
//--------------------------------------------------//
void SellTitle()
{
    currentMenu = 0;

    //Record
    MyClass record;

    //Clear screen
    ClearScreen();
    Header();
    cout << " Sell a Title" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " To sell a title, provide an existing title first."<< endl;
    cout << " Then provide the count sold." << endl << endl << endl << endl;

    //Ask user
    string input;
    cout << endl << endl << " Enter the title of the title sold: ";
    cin >> input;

    //Find title
    int pos = 0;
    primaryInx->matchTitle(input, pos);

    //If title found, then throw an error
    if(pos > 0)
    {
        //Open file
        fstream file("output.bin", ios::in | ios::out | ios::binary);

        //Check file
        if(file.is_open())
        {
            //Read in record
            record.readIt(file, pos);

            cout << endl << endl << " -INFORMATION-" << endl << endl;
            cout << " The record for the title: '"
                 << input << "' currently has a count of " << record.get_count() << endl << endl << endl << endl;

            int input_sold = 0;
            cout << endl << endl << " Enter the amount sold: ";
            cin >> input_sold;

            if(input_sold > 0)
            {
                if((record.get_count() - input_sold) < 0)
                {
                    if(record.get_count() < 0)
                        record.set_count(0);

                    cout << endl << endl << " -Notice-" << endl << endl;
                    cout << " Amount sold exceeds current stock" << endl;
                    cout << " The record for the title: '"
                         << input << "' only has a count of " << record.get_count() << endl << endl << endl << endl;
                    PrintTryAgain(SELL);
                } // end if count is good
                else
                {
                    //Preserve price
                    int my_price = 0, my_count = 0;
                    my_price = record.get_price();
                    //Set count
                    record.set_count(record.get_count() - input_sold);
                    my_count = record.get_count();
                    //Write changes
                    record.writeIt(file, pos);

                    //Update zero record
                    record.get_value(file);
                    record.set_count(record.get_count() + input_sold);
                    record.set_price(record.get_price() + my_price*input_sold);
                    record.set_value(file);

                    //Close file
                    file.close();
                    cout << endl << endl << " -INFORMATION-" << endl << endl;
                    cout << " The record for the title: '"
                         << input << "' now has a count of " << my_count << endl << endl << endl << endl;
                    PrintReturn();
                } // end else count too high
            } // end if count is greater than 0
            else
            {
                cout << endl << endl << " -NOTICE-" << endl << endl;
                cout << " Enter a count sold that is greater than 0" << endl << endl << endl << endl;

                //Get user to try again
                PrintTryAgain(SELL);
            } // end else count is less than 0
        } // end if is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for writing does not exist" << endl << endl << endl << endl;
            PrintReturn();
        } // end else not open

    } //end if
    else // Title not found
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The record for the title: '"
             << input << "' does not exist" << endl << endl << endl << endl;

        //Get user to try again
        PrintTryAgain(SELL);

    }// Else Title Not Found
} // end sellATitle

//--------------------------------------------------//
//         Get and display the sold value
//--------------------------------------------------//
void SoldValue()
{
    //Clear screen
    ClearScreen();
    Header();
    cout << " Sold Value" << endl
         << endl  << endl  << endl;

    //Total value
    int total_value = 0;
    int total_sold = 0;
    string s;

    //Read in file
    fstream file("output.bin", ios::in | ios::binary);

    MyClass record;
    if(file.is_open())
    {
        total_value = record.get_value(file);
        total_sold = record.get_count();
        //Close file
        file.close();
        cout << " -INFORMATION-" << endl << endl;
        cout <<  " Total sold value of all " << total_sold << " sold items" << endl << endl;
        cout << "-----------------" << endl;
        cout << " Total: $" << total_value << endl;
        cout << "-----------------" << endl;
        cout << endl << endl << " Press Enter to return to the Main Menu";
        getline(cin, s);
        getline(cin, s);
        LoadCurrentMenu();
    } // if file is open
    else
    {
        cout << endl << endl << " -NOTICE-" << endl << endl;
        cout << " The file for reading does not exist" << endl << endl << endl << endl;

        //Ask user to return a menu
        PrintReturn();
    } // end file not open
} // end soldValue

//--------------------------------------------------//
//     Add a new record with given attributes
//--------------------------------------------------//
void AddRecord()
{
    currentMenu = 8;

    //Record
    MyClass record;

    //Clear screen
    ClearScreen();
    Header();
    cout << " Adding a new record" << endl
         << endl  << endl  << endl;

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
        PrintTryAgain(ADD_BY_TITLE);

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
            //Open Binary file for binary|writing using fstream
            fstream outputFile("output.bin", ios::in | ios::out | ios::binary);
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
                    if(!CheckDeadFlags(outputFile, nextIndex))
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
                artistInx->addArtist(my_artist, nextIndex);
                yearInx->addYear(my_year, nextIndex);

                //Success!
                cout << endl << endl << " -INFORMATION-" << endl << endl;
                cout <<  " The title: '" << my_title
                     << "' was successfully added at index '" << nextIndex << "'."  << endl;
                cout << "--------" << endl;
                cout << me  << endl << endl;

            } // if file is open
            else
            {
                cout << endl << endl << " -NOTICE-" << endl << endl;
                cout << " The file for reading does not exist" << endl << endl << endl << endl;
            } // end file not open


            //Ask user to return a menu
            PrintReturn();
        } // If Info filled in filled in correctly
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The record for the title: '"
                 << my_title << "' has invalid fields." << endl;
            cout << " Please make sure to fill in a valid value for each field." << endl;
            cout << " Also, use '_' instead of spaces." << endl << endl << endl << endl;
            //Get user to try again
            PrintTryAgain(ADD_BY_TITLE);

        } // Else Info not filled in correctly

    }// Else Title Not Found
} // end addARecord


//--------------------------------------------------//
//           Delete Menu Functions
//--------------------------------------------------//


//--------------------------------------------------//
//          Ask user to confirm deletion
//--------------------------------------------------//
bool ConfirmDelete()
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
        case('Y') :
            isYes = true;
            break;
        case('y') :
            isYes = true;
            break;
        default:
            isYes = false;
            break;
        } // end switch
    } // end else

    return isYes;
} // end confirmDelete

//--------------------------------------------------//
//           Delete a record by Title
//--------------------------------------------------//
void DeleteByTitle()
{
    //Record
    MyClass record;

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

    //If title found, delete it
    if(pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " The record for the title: '" << input << "' can be deleted at index '" << pos << "'." << endl << endl << endl << endl;

        fstream file("output.bin", ios::in | ios::out | ios::binary);
        if(file.is_open())
        {
            cout << "--------" << endl;
            //Display record
            record.readIt(file, pos);
            cout << record;

            if(ConfirmDelete())
            {
                DeleteRecord(file, pos);

                //Success!
                cout << endl << " -INFORMATION-" << endl << endl;
                cout <<  " Delete operation successful." << endl;
                cout << " The index: '" << pos << "' is now available." << endl;
                cout << " The record for the title: '" << input << "' was deleted." << endl << endl << endl << endl;
                file.close();
            } // end if confirm
            else
            {
                file.close();
                cout << endl << " -INFORMATION-" << endl << endl;
                cout <<  " Delete operation canceled." << endl;
                cout << " No records were affected." << endl << endl << endl << endl;
            }
        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open

        //Ask user to return a menu
        PrintReturn();

    } //end if
    else // Title not found
    {
        cout << endl << " -NOTICE-" << endl << endl;
        cout <<  " Delete operation canceled."<< endl;
        cout << " No records were affected." << endl;
        cout << " The record for the title: '" << input << "' could not found for deletion." << endl << endl << endl << endl;

        //Ask user to try again
        PrintTryAgain(DELETE_BY_TITLE);
    }
} // end deleteByTitle

//--------------------------------------------------//
//  Delete records with the given artist or year
//--------------------------------------------------//
void DeleteByArtistYear(recordMember member)
{
    string type;

    switch (member)
    {
    case(ARTIST) :
        type = "artist";
        break;
    case(YEAR) :
        type = "year";
        break;
    default : // Nothing
        break;
    }
    //Record
    MyClass record;

    //Clear screen
    ClearScreen();
    Header();
    cout << " Delete by " << type << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " To delete a record, provide an existing " << type << " first."<< endl;
    cout << " Then confirm the deletion of all records with the same " << type << "." << endl << endl << endl << endl;

    //Ask user
    string input;
    cout << endl << endl << " Enter the " << type << " of the records for deletion: ";
    cin >> input;

    //Find title
    int* pos;
    switch (member)
    {
    case(ARTIST) :
        pos = artistInx->findArtist(input);
        break;
    case(YEAR) :
        pos = yearInx->findYear(atoi(input.c_str()));
        break;
    default : //Nothing
        break;
    }

    //If artist/year found, ask to delete it
    if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << "'" << *pos << "' record(s) found." << endl << endl << endl << endl;


        fstream file("output.bin", ios::in | ios::out | ios::binary);
        if(file.is_open())
        {
            for(int i = 1; i < 11; ++i)
            {
                int position = *(pos + i);

                if(position == 0)
                    break;

                cout << endl << endl << " -INFORMATION-" << endl << endl;
                cout << "The record for the index '" << position << "' can be deleted." << endl;

                cout << "--------" << endl;
                //Display record
                record.readIt(file, position);
                cout << record;

                if(ConfirmDelete())
                {
                    DeleteRecord(file, position);

                    //Success!
                    cout << endl << " -INFORMATION-" << endl << endl;
                    cout <<  " Delete operation successful." << endl;
                    cout << " The index: '" << position << "' is now available." << endl;
                    cout << " The record at index: '" << position << "' was deleted." << endl << endl << endl << endl;

                } // end if confirm
                else
                {
                    cout << endl << " -INFORMATION-" << endl << endl;
                    cout <<  " Delete operation canceled." << endl;
                    cout << " No records were affected." << endl << endl << endl << endl;
                }
            } // end for
            file.close();
        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open

        //Ask user to return a menu
        PrintReturn();

    } //end if record found
    else // Record not found
    {

        cout << endl << " -NOTICE-" << endl << endl;
        cout << " No records were affected."<< endl;
        cout << " The records for the " << type << " '" << input << "' could not be found." << endl << endl << endl << endl;

        //Ask user to try again
        switch (member)
        {
        case(ARTIST) :
            PrintTryAgain(DELETE_BY_ARTIST);
            break;
        case(YEAR) :
            PrintTryAgain(DELETE_BY_YEAR);
            break;
        default : //Nothing
            break;
        }
    }//else
} // end deleteByArtistYear

//--------------------------------------------------//
//          Change Record Menu Functions
//--------------------------------------------------//


//--------------------------------------------------//
//         Change records' artist or year
//--------------------------------------------------//
void ChangeByArtistYear(recordMember member)
{
    string type;

    switch (member)
    {
    case(ARTIST) :
        type = "artist";
        break;
    case(YEAR) :
        type = "year";
        break;
    default : // Nothing
        break;
    }

    //Record
    MyClass record;

    //Clear screen
    ClearScreen();
    Header();
    cout << " Changing by " << type << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " To change a record, provide an existing " << type << " first."<< endl;
    cout << " Then provide a new " << type << "." << endl << endl << endl << endl;

    //Ask user
    string old_input;
    cout << endl << endl << " Enter the " << type << " of the records that are to be updated: ";
    cin >> old_input;

    //Find title
    int* pos;
    switch (member)
    {
    case(ARTIST) :
        pos = artistInx->findArtist(old_input);
        break;
    case(YEAR) :
        pos = yearInx->findYear(atoi(old_input.c_str()));
        break;
    default : //Nothing
        break;
    }

    //If artist/year found, ask to change it
    if(*pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << "'" << *pos << "' record(s) found." << endl << endl << endl << endl;

        //Ask user
        string new_input;
        cout << endl << endl << " Enter the new " << type << " for these records: ";
        cin >> new_input;

        //Read in file
        fstream outputFile("output.bin", ios::in | ios::out | ios::binary);

        if(outputFile.is_open())
        {
            for(int i = 1; i < (*pos + 1); ++i)
            {
                //Set position
                int position = *(pos + i);

                //Read in the record
                record.readIt(outputFile, position);

                //Update data member
                switch (member)
                {
                case(ARTIST) :
                    record.set_artist(new_input);
                    break;
                case(YEAR) :
                    record.set_year(atoi(new_input.c_str()));
                    break;
                default : //Nothing
                    break;
                }

                //Write out the record
                record.writeIt(outputFile, position);

                //Success!
                cout << endl << " -INFORMATION-" << endl << endl;
                cout <<  " Change operation successful." << endl;
                cout << " The record at index: '" << position << "' has been updated." << endl;
                cout << "--------" << endl;
                cout << record;

            } // end for

            outputFile.close();

            //Update appropriate index
            switch (member)
            {
            case(ARTIST) :
                artistInx->updateArtist(old_input, new_input);
                break;
            case(YEAR) :
                yearInx->updateYear(atoi(old_input.c_str()), atoi(new_input.c_str()));
                break;
            default : //Nothing
                break;
            }

        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;
        } // end file not open

        //Ask user to return a menu
        PrintReturn();

    } //end if record found
    else // Record not found
    {
        cout << endl << " -NOTICE-" << endl << endl;
        cout << " No records were affected."<< endl;
        cout << " The records for the " << type << " '" << old_input << "' could not be found." << endl << endl << endl << endl;

        //Ask user to try again
        switch (member)
        {
        case(ARTIST) :
            PrintTryAgain(CHANGE_BY_ARTIST);
            break;
        case(YEAR) :
            PrintTryAgain(CHANGE_BY_YEAR);
            break;
        default : //Nothing
            break;
        }
    } // end else
} // end changeByArtistYear

//--------------------------------------------------//
//   Ask for a title to change every attribute
//--------------------------------------------------//
void ChangeByTitlePreMenu()
{
    //Record
    MyClass record;

    //Clear screen
    ClearScreen();
    Header();
    cout << " Changing by Title" << endl
         << endl  << endl  << endl;

    //Provide general information
    cout << " -INFORMATION-" << endl << endl;
    cout <<  " To change a record, provide an existing title first."<< endl;
    cout << " Then provide any changes on the next menu." << endl << endl << endl << endl;

    //Ask user
    string input;
    cout << endl << endl << " Enter the title of the record that is to be updated: ";
    cin >> input;

    //Find title
    int pos = 0;
    primaryInx->matchTitle(input, pos);

    //If title found, ask to change it
    if(pos > 0)
    {
        cout << endl << endl << " -INFORMATION-" << endl << endl;
        cout << " A record was found at index: " << pos << endl << endl << endl << endl;

        //Create record to be passed
        MyClass me;

        //Read in record
        fstream file("output.bin", ios::in | ios::binary);
        if(file.is_open())
        {
            me.readIt(file, pos);
            file.close();

            //Move to actual menu
            input = "";
            cout << endl << endl << " Press Enter to continue ";
            getline(cin, input);
            getline(cin, input);

            ChangeByTitleMenu(me, pos);
        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for reading does not exist" << endl << endl << endl << endl;

            //Ask user to return a menu
            PrintReturn();
        } // end file not open
    } //end if record found
    else // Record not found
    {
        cout << endl << " -NOTICE-" << endl << endl;
        cout << " No records were affected."<< endl;
        cout << " The record for the title '" << input << "' could not be found." << endl << endl << endl << endl;

        PrintTryAgain(CHANGE_BY_TITLE);

    } // end else
} // end ChangeByTitlePreMenu

//--------------------------------------------------//
//  Change a record by title menu selection control
//--------------------------------------------------//
void ChangeByTitle(int selection, MyClass& me, const int position)
{
    if(selection == 1)
    {
        //Unset flags
        flag_titleChanged = false;
        flag_artistChanged = false;
        flag_yearChanged = false;

        //Go to Change By Menu
        currentMenu = 7;
        LoadCurrentMenu();
    }
    else if(selection == 2)
    {
        //Submit
        fstream file("output.bin", ios::in | ios::out | ios::binary);
        if(file.is_open())
        {
            MyClass old_record;
            old_record.readIt(file, position);

            //Update any changed indexes
            if(flag_titleChanged)
            {
                //Update title index
                int title_pos = 0;
                primaryInx->updateTitle(old_record.get_title(), me.get_title(), title_pos);
            }
            if(flag_artistChanged)
            {
                //Update artist index
                artistInx->updateArtist(old_record.get_artist(), me.get_artist());
            }
            if(flag_yearChanged)
            {
                //Update year index
                yearInx->updateYear(old_record.get_year(), me.get_year());
            }

            me.writeIt(file, position);
            cout << endl << endl << " -INFORMATION-" << endl << endl;
            cout << " The record at index: " << position << " was successfully updated." <<endl << endl << endl << endl;
            cout << me;
            file.close();
        } // if file is open
        else
        {
            cout << endl << endl << " -NOTICE-" << endl << endl;
            cout << " The file for writing does not exist" << endl << endl << endl << endl;
        } // end file not open

        //Unset flags
        flag_titleChanged = false;
        flag_artistChanged = false;
        flag_yearChanged = false;

        //Ask to return
        currentMenu = 7;
        //Ask user to return a menu
        PrintReturn();
    }
    else if(selection == 3)
    {
        //Change Title
        string my_title;
        cout << endl << " Enter the new title: ";
        cin >> my_title;
        int temp;
        if(primaryInx->matchTitle(my_title, temp))
        {
            cout << " This title already exists. Title reset.";
            getline(cin, my_title);
            getline(cin, my_title);
        }
        else
        {
            me.set_title(my_title);
            //Set Flag
            flag_titleChanged = true;
        }

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
    else if(selection == 4)
    {
        //Change Artist
        string my_artist;
        cout << endl << " Enter the new artist: ";
        cin >> my_artist;
        me.set_artist(my_artist);

        //Set Flag
        flag_artistChanged = true;

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
    else if(selection == 5)
    {
        //Change Type
        string my_type;
        cout << endl << " Enter the new type: ";
        cin >> my_type;
        me.set_type(my_type);

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
    else if(selection == 6)
    {
        //Change Year
        int my_year;
        cout << endl << " Enter the new year: ";
        cin >> my_year;
        me.set_year(my_year);

        //Set Flag
        flag_yearChanged = true;

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
    else if(selection == 7)
    {
        //Change Price
        int my_price;
        cout << endl << " Enter the new price: ";
        cin >> my_price;
        me.set_price(my_price);

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
    else if(selection == 8)
    {
        //Change Count
        int my_count;
        cout << endl << " Enter the new count: ";
        cin >> my_count;
        me.set_count(my_count);

        //Return to menu
        ChangeByTitleMenu(me, position);
    }
} // end changeByTitle

//--------------------------------------------------//
//           Check for a Dead Record slot
//--------------------------------------------------//
bool CheckDeadFlags(fstream& input, int& pos)
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
} // end checkDeadFlags

//--------------------------------------------------//
//   Delete a record from binary file and indexes
//--------------------------------------------------//
void DeleteRecord(fstream& file, const int& pos)
{
    MyClass record;
    //Read record
    record.readIt(file, pos);
    //Delete Title Index
    primaryInx->deleteTitle(record.get_title());
    //Delete Artist Index
    artistInx->deleteArtist(record.get_artist(), pos);
    //Delete Year Index
    yearInx->deleteYear(record.get_year(), pos);
    //Declare dead
    record.set_flag();
    //Write out that change (Dead)
    record.writeIt(file, pos);
} // end deleteRecord

//END console.cpp
