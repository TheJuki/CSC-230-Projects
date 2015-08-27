//Justin Kirk
//Practice 2

#include <iostream>
#include <string>
using namespace std;

//Declarations
void manipTwo(int&, int);
int add2(const int&, const int&);

int main()
{
    int a = 1, b = 2, sum;
    string s;
    cout << "Prior to manipTwo, a = " << a << " and b = " << b << endl;
    // endl above = end-line '\n'.
    manipTwo(a,b);
    cout << "After call to manipTwo, a = " << a << " and b = " << b << endl;

    //Can you explain what happened above?
    //Yes. 'a' is passed by reference so a change to 'a' in maniTwo
    //is an actual change to that variable.
    sum = add2(a, b);
    cout << "Sum of " << a << " + " << b << " = " << sum << endl;
    getline(cin,s);
    return(0);
}

void manipTwo(int& one, int two)
{
    one = 100; //Modified
    two = 100; //Not Modified
}

int add2(const int& one, const int& two)
{
    return (one + two);
}

