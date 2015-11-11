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
        class Node
        {
            public:
                int year;
                int pos;
                Node * next;
                Node * prev;
                Node * up;
                Node * down;
                Node():year(-1), pos(-1), next(NULL), prev(NULL), up(NULL), down(NULL) { }
                Node(int A, int P): year(A), pos(P)
                {
                    next=prev=up=down=NULL;
                }
        };
        Node * head;
        Node * tail;
        unsigned int size;
        void writeSecondary();
        void readSecondary();
        void killList();
        void delete_by_Year(int T);
        void delete_by_pos(int P);
    public:
        YearIndex(): size(0)
        {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
        }
        YearIndex(int my_size): size(my_size)
        {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
            readSecondary();
        } // readFile will change size
        ~YearIndex()
        {
            writeSecondary();
            killList();
        }
        void addYear(int my_Year, int my_key);
        void updateYear(int old_Year, int new_Year);
        int matchYear(int inYear);
        bool deleteYear(int T, int P);
        int * findYear(int inYear);
        bool matchYear(int inYear, int pos[]);
};
#endif // YEAR_H

