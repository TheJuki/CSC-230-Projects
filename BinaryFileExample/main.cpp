#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class MyClass
{
private:
    int x;
    float y;

public:
    MyClass():x(0), y(0) {}

    void set (int newX, float newY)
    {
        x = newX;
        y = newY;
    }

    void writeIt(fstream& out, int position) const;
    void readIt(fstream& input, int position) const;

    friend ostream& operator<<(ostream& out, const MyClass& someObject);
};

//Class Methods ======================

void MyClass::writeIt(fstream& out, int position) const
{
    //write out the MyClass object
    out.seekp(position * (sizeof(MyClass)));
    out.write((char*) this, sizeof(MyClass));
}

void MyClass::readIt(fstream& input, int position) const
{
    //read in the MyClass object
    input.seekg(position * (sizeof(MyClass)));
    input.read((char*) this, sizeof(MyClass));
}

//Class Friends =========================

ostream& operator <<(ostream& out, const MyClass& someObject)
{
    out << someObject.x << " -- " << someObject.y << endl;
    return out;
}

// Free Functions ========================

bool fileExists(char* filename)
{
    ifstream tryIt(filename, ios::in);
    //tryIt would hold a NULL value (0 which is false)
    if(!tryIt)
    {
        return false;
    }
    else
    {
        tryIt.close();
        return true;
    }
} // fileExists

long fileSize(char* fileName)
{
    ifstream tryIt(fileName, ios::in);

    //check to see if the file exists

    if(!tryIt)
    {
        return -1;
    }
    else
    {
        tryIt.seekg(0, ios::end);

        long answer = tryIt.tellg();
        tryIt.close();
        return answer;
    }
} // fileSize

int main(void)
{
    char outputFileName[80];
    int pos = 0;
    do
    {
        cout << "Enter a name (not now in use) for an output file : ";
        cin >> outputFileName;

        if(fileExists(outputFileName))
        {
            cout << "A file by that name already exists! Try again."  << endl;
        }
    } while (fileExists(outputFileName));

    // Available access modes:
    // ios::in     - open file for reading
    // ios::out    - open file for writing
    // ios::trunc  - truncate the file to have size 0 before reading/writing
    // ios::binary - open file in binary mode (not text mode)

    fstream outputFile(outputFileName, ios::out | ios::binary);

    if(!outputFile)
    {
        cout << "Unable to open '" << outputFileName << "' for output." << endl;
        return(1);
    }
    else
    {
        cout << "Output file correctly opened." << endl;
    }

    // Create a MyClass object using default constructor
    MyClass myObject;
    // write out 14 records using the same MyClass object
    for (int i = 1; i < 15; i++)
    {
        // modify Object
        myObject.set(i, i * 2.0f);

        myObject.writeIt(outputFile, pos);
        pos ++;
    }

    outputFile.close();

    if(!outputFile)
    {
        cout << "Unable to open '" << outputFile << "' for re-reading." << endl;
        return(1);
    }
    else
    {
        cout << "File correctly re-opened." << endl;
    }

    // Read and echo entire file
    pos = 0;
    myObject.readIt(outputFile, pos);
    while(!outputFile.eof())
    {
        cout << myObject;
        pos++;
        myObject.readIt(outputFile, pos);
    }
    outputFile.close();

    //Mess with direct access
    outputFile.open(outputFileName, ios::in | ios::binary);
    long inputFileSize = fileSize(outputFileName);

    cout << "Size of file in bytes      = " << inputFileSize << endl;
    cout << "Bytes per record (Object) = " << sizeof(myObject)
         << " (an int and a float)." << endl;
    cout << "Number of record in file = " << inputFileSize / sizeof(myObject)
         << endl;

    if(inputFileSize % sizeof(myObject) != 0)
    {
        cout << "Something is funny about that file size!!!" << endl;
    }

    myObject.readIt(outputFile, 2);
    cout << "Record 3 holds: " << myObject;

    myObject.readIt(outputFile, 8);
    cout << "Record 9 holds: " << myObject;

    myObject.readIt(outputFile, 7);
    cout << "Record 8 holds: " << myObject;
    outputFile.close();

    outputFile.open(outputFileName, ios::in | ios::out | ios::binary);
    cout << "We will now do direct access to update record 8 in that file.\n";

    myObject.set(88, 3.14f);
    myObject.writeIt(outputFile, 7);
    myObject.readIt(outputFile, 7);

    cout << "Record 8 now holds " << myObject;
    cout << "Above line should show 88 and 3.14." << endl;
    outputFile.close();


}
