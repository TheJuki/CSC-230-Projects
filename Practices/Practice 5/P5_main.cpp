//Justin Kirk
//Practice 5

#include <iostream>
#include <string>

using namespace std;

//Prototype
int findCharInString(const string, char);

int main()
{
    string name1 = "Hello from CIS!";
    string name2, name3, name4, name5, s;
    int where;

    name2 = "Mobile";
    cout << name1 << endl
         << name2 << " welcomes you!" <<endl;
    cout << "From that first line, characters 2 to 7 (positions 1 to 6) are: ";
    for (int i = 1; i <= 6; i++)
        cout << name1[i] << endl;
    name3 = "Hi there!";
    cout << name3 << endl;
    name4 = name3;
    cout << "Once again..." << name4 << endl
         << "name3 = " << name3 << endl << "name4 = " << name4 << endl;
    if (name3 == name4)
        cout << "So... it looks like name3 and name4 are equal!\n";
    else
        cout << "name3 and name4 are not equal.\n";
    cout << "name1 = " << name1 << endl << "name4 = " << name4 << endl;

    if(name1 == name4)
        cout << "So... it looks like name1 and name4 are equal!\n";
    else if(name1 < name4)
        cout << "name1 is less than name4.\n";
    else
        cout << "name1 is greater than name4.\n";

    name5 = name3 + name4;
    cout << "name3 and name4 back to back: " << name5 << endl;

    where = findCharInString(name4, 'X');

    if(where != -1)
        cout << "'" << name3 << "' has an 'X' in position " << where << endl;
    else
        cout << "'" << name3 << "' does not contain an 'X'\n";

    if(findCharInString(name3, 't') != -1)
        cout << "'" << name3 << "' has a 't' in position " << where << endl;
    else
        cout << "'" << name3 << "' does not contain an  't'\n";

    cout << "name1 = '" << name1 << "' and length = " << name1.length() << endl
         << "name2 = '" << name2 << "' and length = " << name2.length() << endl
         << "name3 = '" << name3 << "' and length = " << name3.length() << endl
         << "name4 = '" << name4 << "' and length = " << name4.length() << endl
         << "name5 = '" << name5 << "' and length = " << name5.length() << endl;

    cout << "Enter your name full name : ";
    getline(cin,name5);
    cout << "Hi there " << name5 << endl;
    cout << "Note, using getline version reading name gets full string!" << endl;
    cout << "Enter full name again: ";
    cin >> name5;
    cout << "Hi there " << name5 << endl;
    cout << "Note: reading into a string variable only goes up to a blank." << endl;
    cout << "name1.substr(6,4) yields -> \'" << name1.substr(6,4) << "\'" << endl;
    getline(cin,s);
    return(0);
} // end main()

int findCharInString(const string source, char seeking)
{
    int answer = -1;
    for(int i = 0; (i < source.length()) && (answer == -1); i++)
        if(source[i] == seeking)
            answer = i;
    return(answer);
}
