#ifndef Node_H
#define Node_H
#include "Node.h"
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

