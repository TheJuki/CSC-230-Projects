//Justin Kirk
//Practice 4
//P4_main.cpp

#include <iostream>
#include <string>

#include "my_other.h"
using namespace std;

int main()
{
    int myArray[10];
    int lastCellUsed, target, whereFound;
    string s;

    cout << "Load array myArray" << endl;
    fillArray(myArray, 10, lastCellUsed);
    bubbleSort(myArray, lastCellUsed);
    cout << "Array is now sorted (via bubblesort)." << endl;

    do {

        cout << "Enter number to find (999 to quit): ";
        cin >> target;
        if (target != SENTINEL)
        {
            if (binarySearch(myArray, lastCellUsed, target, whereFound))
                cout << "Found " << target << " in cell " << whereFound
                    << endl;
            else
                cout << "Failed to find " << target << " in the array. \n";
        }
    } while (target != SENTINEL);
    getline(cin,s);
    return(0);
} //main()
