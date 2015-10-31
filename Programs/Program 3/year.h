/*
File       : year.h
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Header for year.cpp
*/

#ifndef YEAR_H
#define YEAR_H

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

class YearIndex
{
private:
     class Y_Node {

    public:
        std::string artist;
        int pos;
        Y_Node * next;
        Y_Node * prev;
        Y_Node():artist("no"), pos(-1), next(NULL), prev(NULL) {}
        Y_Node(std::string T, int P): artist(T), pos(P), next(NULL), prev(NULL) {}
    };
    Y_Node * head;
    Y_Node * tail;
    int size;

public:
    YearIndex(): size(0)
    {
        head = new Y_Node(" ", -1);
        tail = new Y_Node("~", -1);
        head->next = tail;
        tail->prev = head;
    }
    YearIndex(int InSize):size(InSize)
        {
            head = new Y_Node(" ", -1);
            tail = new Y_Node("~", -1);
            head->next = tail;
            tail->prev = head;
            readSecondary();
        }
    ~YearIndex() {kill_Y_List();}

    int getYear(int pos) const;
    void addYear(int myYear, int myKey);
    void updateYear(int old_year, int new_year);
    int * findYear(int inYear);
    void writeSecondary();
    void readSecondary();
    bool matchYear(int inYear, int pos[]);
    bool deleteYear(int inYear, int pos);
    void kill_Y_List();
};
#endif // YEAR_H

