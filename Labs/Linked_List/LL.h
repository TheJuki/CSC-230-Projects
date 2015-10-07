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

    bool AddHead(string d, int k);
    bool AddTail(string d, int k);
    bool AddIn(string d, int k);

public:
    LL()
    {
        h = t = NULL;
    }

    ~LL()
    {
       // killList();
    }

    void killList();
    bool Add(string d, int k);
    bool Delete(string d);

};

#endif // LL_H

