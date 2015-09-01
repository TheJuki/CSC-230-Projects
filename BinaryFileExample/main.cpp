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
    ifstream tryIt(filename, ios::in);

    //check to see if the file exists

    if(!tryIt)
    {
        return -1;
    }
    else
    {
        tryIt.seekg(0, ios::end);

        long answer = tryIt.tellg;
        tryIt.close();
        return answer;
    }
} // fileSize

int main(void)
{
    char
}
