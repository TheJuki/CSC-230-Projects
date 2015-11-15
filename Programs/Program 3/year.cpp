/*
File       : year.cpp
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Code for year data
*/

#include "year.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

//Add a year (Sort alphabetically) (1,2,3)
void YearIndex::addYear(int Y, int P)
{
    bool foundYear = false;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == Y)
        {
            foundYear = true;
            wp->up->pos = wp->up->pos + 1;
            Node * holdUp = wp->up;
            while(holdUp->up != NULL)
            {
                holdUp = holdUp->up;
            } // end while
            Node * wp2 = new Node(-1,P);
            wp2->down = holdUp->down;
            wp2->up = holdUp;
            holdUp->down->up=wp2;
            holdUp->down=wp2;
            break;
        } // end if
        wp = wp->next;
    } // end while

    //Add a new year
    if(!foundYear)
    {
        if(head->year>Y)
        {
            Node * wp = new Node(Y, P);
            wp->prev = NULL;
            wp->next = head;
            head->next = wp;
            head = wp;
            size += 1;

            head->up = new Node(-1, 1);
            head->up->up = new Node(-1, P);
            head->up->up->down =  head->up;
        } // end if
        else if(tail->year<Y)
        {
            Node * wp = new Node(Y, P);
            wp->next = NULL;
            wp->prev = tail;
            tail->prev = wp;
            tail = wp;
            size += 1;

            tail->up = new Node(-1, 1);
            tail->up->up = new Node(-1, P);
            tail->up->up->down =  tail->up;
        } // end else if
        else
        {
            Node * wp = head->next;
            while(wp != NULL)
            {
                if(wp->year>Y)
                {
                    Node * wp2 = new Node(Y,P);
                    wp2->prev = wp->prev;
                    wp2->next = wp;
                    wp->prev->next=wp2;
                    wp->prev=wp2;
                    size += 1;

                    wp->prev->up = new Node(-1, 1);
                    wp->prev->up->up = new Node(-1, P);
                    wp->prev->up->up->down =  wp->prev->up;
                    return;
                } // end if
                wp=wp->next;
            } // end while
        } // end else
    } // end if
} // end addYear

//Update a year
void YearIndex::updateYear(int old_year, int new_year, int old_pos)
{
    int holdLocation = 0;

    //If new year does not currently exist...
    if(!matchYear(new_year, holdLocation))
    {
        addYear(new_year, old_pos);
    } // end if
    else
    {
        //Copy positions to new location

        Node * newNode = head->next;

        //Find new Node
        while(newNode != NULL)
        {
            if(newNode->year == new_year)
            {
                break;
            } // end if
            newNode = newNode->next;
        } // end while

        //Update count
        newNode->up->pos = newNode->up->pos + 1;

        //Find empty up in newNode
        Node * newUp = newNode->up;
        while(newUp->up != NULL)
        {
            newUp = newUp->up;
        } // end while

        //Add New Up
        Node * p = new Node(-1,old_pos);
        p->down = newUp->down;
        p->up = newUp;
        newUp->down->up=p;
        newUp->down=p;

    } // end else
    //Delete Old Up
    deleteYear(old_year, old_pos);
} // end updateYear

//Display all years
void YearIndex::getAllYears()
{

    Node * wp = head->next;

    std::cout << size << std::endl;
    while(wp != NULL)
    {
        if(wp->up != NULL)
        {
            Node * holdUp = wp->up;
            int i = 0;
            std::vector<int> myVector;
            while(holdUp->up != NULL)
            {
                myVector.insert(myVector.begin() + i, holdUp->pos);
                holdUp = holdUp->up;
                ++i;
            } // end while

            std::string buildLine = "";
            for(i = 0; i < myVector.size(); ++i)
            {
                std::stringstream strs;
                strs << myVector.at(i);
                std::string temp_str = strs.str();

                buildLine += temp_str + " ";
            } // end for
            std::cout << wp->year << " " << buildLine << std::endl;
        } // end if

        wp = wp->next;
    } //end while
} // end getAllYears

//Write out years
void YearIndex::writeSecondary()
{
    std::ofstream fout("year_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    Node * wp = head->next;

    //For each item in Linked List
    while(wp != NULL)
    {
        //Default
        buildLine = " ";
        //Number of Keys
        std::stringstream strs;
        if(wp->up != NULL)
        {
            strs << wp->up->pos;
            std::string temp_str = strs.str();
            //Add number of keys to numOfKeys
            numOfKeys = temp_str + " ";

            Node * holdUp = wp->up->up;
            //for each item in pos
            while(holdUp != NULL)
            {
                if(holdUp->pos != 0)
                {
                    //Convert the key to a string
                    std::stringstream strs;
                    strs << holdUp->pos;
                    std::string temp_str = strs.str();
                    //Add key to buildLine
                    buildLine += temp_str + " ";
                } //end if
                holdUp = holdUp->up;
            } // end while

            //If there is at least 1 key then write to file
            if(wp->up->pos != 0)
            {
                //Write to file
                fout << numOfKeys
                     << wp->year
                     << buildLine
                     << std::endl;
            } // end if
        } // end if
        wp = wp->next;
    } //end while

    //Close file
    fout.close();
} // end writeSecondary

//Read in years
void YearIndex::readSecondary()
{
    std::ifstream input("year_index.txt");
    std::string line;
    getline (input,line);
    size = atoi(line.c_str());

    if (input.is_open())
    {
        //Set position to 1
        long position = 1;
        //delimiter is a space
        std::string delimiter = " ";
        //size of string
        size_t pos = 0;
        //Line in file as a string
        std::string line;
        //string of part
        std::string part;
        //Number of keys in line
        int numOfKeys = 0;
        //Year Input
        int year_input = -1;
        while(!input.eof() && position != (int)(size+1))
        {
            //Read in a line from the sequential file
            getline (input,line);

            //Defaults
            pos = 0;
            part = "";
            numOfKeys = 0;

            //Get Number of keys
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                numOfKeys = atoi(part.c_str());
            } // end if

            //Get year
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                year_input = atoi(part.c_str());
                line.erase(0, pos + delimiter.length());
                --size;
            } // end if

            //Set pos to keys in line
            for(int i = 0; i < numOfKeys; ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    addYear(year_input, atoi(part.c_str()));
                    line.erase(0, pos + delimiter.length());
                } // end if
            } // end for

            position++;
        } // End eof while
        input.close();
    } // end if
} // end readSecondary

//Find a year and return an array of positions
std::vector<int> YearIndex::findYear(int inYear)
{
    std::vector<int> myVector;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == inYear)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                Node * holdUp = wp->up;
                int i = 0;

                while(holdUp != NULL)
                {
                    myVector.insert(myVector.begin() + i, holdUp->pos);
                    holdUp = holdUp->up;
                    ++i;
                } // end while
                break;
            } // end if
            else
                break;
        } // end if
        wp = wp->next;
    } // end while

    return myVector;
} // end findYear

//Match a year
bool YearIndex::matchYear(int inYear, int &pos)
{
    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == inYear)
        {
            pos = wp->up->pos;
            return true;
        } // end if
        wp = wp->next;
    } // end while
    pos = 0;
    return false;
} // end matchYear

//Delete a year
bool YearIndex::deleteYear(int inYear, int pos)
{
    Node * wp = head->next;
    Node * holdUp, * hold;

    while(wp != tail)
    {
        if(inYear == wp->year)
        {
            if(wp->up != NULL)
            {
                holdUp = wp->up->up;
                while(holdUp != NULL)
                {
                    hold = holdUp;
                    holdUp = holdUp->up;
                    if(hold->pos == pos)
                    {
                        wp->up->pos = wp->up->pos - 1;
                        if(hold->down != NULL)
                            hold->down->up = hold->up;
                        if(hold->up != NULL)
                            hold->up->down = hold->down;
                        delete hold;
                    }
                } // end while
            } // end if
            if(wp->up->pos == 0)
            {
                hold = wp;
                wp->next->prev = wp->prev;
                wp->prev->next = wp->next;
                delete hold;
                size--;
            }

            return true;
        } // end if
        wp = wp->next;
    } // end while
    return false;
} // end deleteYear

//Kill Linked Lists upon delete
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
            } // end while
        } // end if
        hold = wp;
        wp = wp->next;
        delete hold;
    } // end while
    return;
} // end killList

