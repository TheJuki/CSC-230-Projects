//Justin Kirk
//Practice 8
//main

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Prototypes
void openInputFile (ifstream& theFile);

void openNewOutputFile (ofstream& theFile);

int main()
{
    ifstream inputFile, inputFile2;
    ofstream outputFile;
    char aChar;
    string line, s;
    int lineCounter;
    openInputFile(inputFile);

    cout << "We will now echo the contents of that file to the screen: " << endl;

    //Modified to include last line in file
    lineCounter = 1;
    while(!inputFile.eof())
    {
        getline(inputFile, line);
        cout << line << endl;

        //Pause every 20 lines
        if (lineCounter % 20 == 0)
        {
            cout << endl << "Hit enter key to continue...";
            getline(cin,s);
        }
        lineCounter++;
    } //while

    //Close files
    inputFile.close();

    //Read char by char
    lineCounter = 0;
    openInputFile(inputFile2);
    cout << "We will now read the file char by char and send to an output file. "
         << endl;
    openNewOutputFile(outputFile);
    inputFile2.get(aChar); //An initial "priming" read

    //Initial line should be counted too
    if(aChar != '\0')
        lineCounter = 1;

    //Start copying
    while(!inputFile2.eof())
    {
        if(aChar == '\n')
            lineCounter++;
        outputFile.put(aChar);
        inputFile2.get(aChar);
    } //while

    //Close files
    inputFile2.close();
    outputFile.close();
    cout << "The file just copied had " << lineCounter << " lines in it." << endl;
    getline(cin, s);
    return(0);
} // main

//Functions

void openInputFile(ifstream& theFile)
{
    string fileName;
    cout << "Enter name of file to read: ";
    getline(cin, fileName);
    theFile.open(fileName.c_str(), ios_base::in); //c_str - Convert to char array
}

void openNewOutputFile(ofstream& theFile)
{
    string fileName;
    cout << "Enter name of output file to create: ";
    getline(cin, fileName);
    theFile.open(fileName.c_str(), ios::out);
}
