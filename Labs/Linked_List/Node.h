/*
File       : Node.h
Program    : Homework 3 Linked List
Due Date   : October 20, 2015
Author     : Justin Kirk
Description: Header Node
*/

#ifndef Node_H
#define Node_H
#include <string>

using namespace std;

class Node
{
    friend class LL;

private:
    string data;
    int year;
    Node* next;
    Node* prev;

public:
    Node():data(""), year(-1) {next = prev = NULL;}
    Node(string str, int y):data(str), year(y)
    {
        next = prev = NULL;
    }
};

#endif

