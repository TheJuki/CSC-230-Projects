//Justin Kirk
//Practice 4

#include <iostream>
#include <string>

#include "my_other.h"
using namespace std;

void fillArray(int theArray[], int maxSize, int& lastUsed)
{
    int input;
    lastUsed = -1;
    do {
        cout << "Enter a number to fill or " << SENTINEL << " to quit: ";
        cin >> input;
        if (input != SENTINEL)
            theArray[++lastUsed] = input;
    } while((input != SENTINEL) && (lastUsed < maxSize - 1));
} // fillArray

void swapInts(int& int1, int& int2) {
    int temp = int1;
    int1 = int2;
    int2 = temp;
} //swampInts

void bubbleSort(int theArray[], int lastCell)
{
    int i, j;
    bool swapMade = true;
    for (i = 0; (i < lastCell) && swapMade; i++)
    {
        swapMade = false;
        for (j = 0; j < lastCell - i; j++)
        {
            if(theArray[j] > theArray[j+1])
            {
                swapInts(theArray[j], theArray[j+1]);
                swapMade = true;
            } // if
        } //for j
    } //for i
} //bubbleSort

bool binarySearch(const int theArray[], int last, int target, int& where)
{
    int low, mid, hi;
    bool found = false;
    where = -1;
    low = 0;
    hi = last;
    while ((!found) && (low <= hi))
    {
        mid = (hi + low) / 2; // int division
        if(theArray[mid] == target)
        {
            found = true;
            where = mid;
        }
        else if(target < theArray[mid])
            hi = mid -1 ;
        else
            low = mid + 1;
    } //while
    return(found);
} //binarySearch
