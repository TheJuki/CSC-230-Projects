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

void YearIndex::addYear(int myYear, int myKey)
{
     bool foundYear = false;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == myYear)
        {
            foundYear = true;
            wp->up->pos = wp->up->pos + 1;
            Node * holdUp = wp->up;
            while(holdUp->up != NULL)
            {
                holdUp = holdUp->up;
            } // end while
            Node * p = new Node(-1,myKey);
            p->down = holdUp->down;
            p->up = holdUp;
            holdUp->down->up=p;
            holdUp->down=p;
            break;
        }
        wp = wp->next;
    } // end while
    if(!foundYear)
    {
        Node * hold = new Node(myYear, myKey);
        hold->next = NULL;
        hold->prev = tail;
        tail->next = hold;
        tail = hold;
        size += 1;
        hold->up = new Node(-1, 1);
        hold->up->up = new Node(-1, myKey);
        hold->up->up->down =  hold->up;
    } // end else
}
void YearIndex::updateYear(int old_Year, int new_Year)
{

}

void YearIndex::getAllYears()
{
    Node * wp = head->next;

    std::cout << size << std::endl;
    while(wp != NULL)
    {
        if(wp->up != NULL)
            std::cout << wp->year << " " << wp->up->up->pos << std::endl;
        wp = wp->next;
    } //end while
}

void YearIndex::writeSecondary()
{
    std::ofstream fout("year_index.txt");

    fout << size << std::endl;

    //A normal string used as a string builder
    std::string buildLine;
    std::string numOfKeys;

    Node * wp = head->next->next;

    //For each item in my_list
    while(wp != NULL)
    {
        //Default
        buildLine = " ";
        //Number of Keys
        std::stringstream strs;
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
        wp = wp->next;
    } //end while

    //Close file
    fout.close();
}

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

        Node * hold = head->next;
        while(!input.eof() && position != size+1)
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
            }

            //Get year
            if ((pos = line.find(delimiter)) != std::string::npos)
            {
                part = line.substr(0, pos);
                year_input = atoi(part.c_str());
                line.erase(0, pos + delimiter.length());
                Node * hold = new Node(year_input, 0);
                hold->next = NULL;
                hold->prev = tail;
                tail->next = hold;
                tail = hold;
                hold->up = new Node(-1, 0);
                hold->up->up = new Node(-1, 0);
                hold->up->up->down = hold->up;
            }

            //Set pos to keys in line
            for(int i = 0; i < numOfKeys; ++i)
            {
                if((pos = line.find(delimiter)) != std::string::npos)
                {
                    part = line.substr(0, pos);
                    addYear(year_input, atoi(part.c_str()));
                    line.erase(0, pos + delimiter.length());
                }
            } // end for

            position++;
            hold = hold->next;
        } // End eof while
        input.close();
    } // end if
}
int * YearIndex::findYear(int inYear)
{
     int emptyArray[1];
    emptyArray[0] = 0;

    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == inYear)
        {
            if(wp->up != NULL && wp->up->up != NULL)
            {
                int arraySize = wp->up->pos;
                Node * holdUp = wp->up->up;
                for(int i = 0; i < 1; ++i)
                {
                    if(holdUp != NULL)
                        emptyArray[0] = holdUp->pos;
                    else
                        break;
                    holdUp = holdUp->up;

                }
                break;
            } // end if
            else
                break;
        }
        wp = wp->next;
    } // end while

    return emptyArray;
}
bool YearIndex::matchYear(int inYear, int &pos)
{
    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->year == inYear)
        {
            pos = wp->up->pos;
            return true;
        }
        wp = wp->next;
    } // end while
    pos = 0;
    return false;
}

bool YearIndex::deleteYear(int inYear, int pos)
{
    Node * wp = head->next;
    Node * wsp, * hold;

    while(wp != tail)
    {
        if(inYear == wp->year)
        {
            if(wp->down != NULL)
            {
                wsp = wp->down;
                while(wsp->down != NULL)
                    wsp = wsp->down;
                while(wsp->up != NULL)
                {
                    // call binary file with pos to delete record
                    hold = wsp;
                    wsp = wsp->up;
                    delete hold;
                }
            }
            // call binary file with pos to delete record
            hold = wp;
            wp->next->prev = wp->prev;
            wp->prev->next = wp->next;
            delete hold;
            return true;
        }
        wp = wp->next;
    }
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

