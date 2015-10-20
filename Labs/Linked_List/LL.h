/*
File       : LL.h
Program    : Homework 3 Linked List
Due Date   : October 20, 2015
Author     : Justin Kirk
Description: Header for LL.cpp
*/

#ifndef LL_H
#define LL_H
#include "Node.h"
#include <string>

using namespace std;

class LL
{
    friend class Node;

private:
    Node * h;
    Node * t;
    int size;
    bool isCircular;

    bool AddHead(string d, int k);
    bool AddTail(string d, int k);
    bool AddIn(string d, int k);

    bool DeleteHead();
    bool DeleteTail();

public:
    LL()
    {
        h = t = NULL;
        isCircular = false;
    }

    ~LL()
    {
       killList();
    }

    void killList();
    Node* getNote();
    bool Add(string d, int k);
    void exchangeNodes(string d1, string d2);
    bool Delete(string d);
    void outputList();
    void makeCircular();

};

#endif // LL_H

