/*
File       : year.cpp
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Code for year data
*/

#include "year.h"

void YearIndex::addYear(int myYear, int myKey)
{

}
void YearIndex::updateYear(int old_Year, int new_Year)
{

}
void YearIndex::writeSecondary()
{

}
void YearIndex::readSecondary()
{

}
int * YearIndex::findYear(int inYear)
{
    static int emptyArray[1];
    emptyArray[0] = 0;
    return emptyArray;
}
bool YearIndex::matchYear(int inYear, int pos[])
{
    return false;
}

bool YearIndex::deleteYear(int inYear, int pos)
{
    return false;
}

void YearIndex::killList()
{
    Node * wp = head;
    Node * wsp = NULL;
    Node * hold;
    while(wp != NULL)
    {
        if(wp->down != NULL)
        {
            wsp = wp->down;
            while(wsp->down != NULL)
                wsp = wsp->down;
            while(wsp->up != NULL)
            {
                hold = wsp;
                wsp = wsp->up;
                delete hold;
            }
        }
        hold = wp;
        wp = wp->next;
        delete hold;
    }
    return;
}

