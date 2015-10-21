/*
File       : main.cpp
Program    : Homework 3 Linked List
Due Date   : October 20, 2015
Author     : Justin Kirk
Description: The main driver for the Linked List homework.
             A. Add to Head / Tail
             B. Delete from Head / Tail
             C. Circular List...
             D. Exchange nodes (3) and (7)
*/

#include <iostream>
#include <string>
#include "LL.h"

using namespace std;

int main()
{
    cout << "Linked List" << endl << endl;
    cout << "Add Nodes 1,2,3,4,5" << endl << endl;
    LL *linkedList = new LL();
    linkedList->Add("1", 1991);
    linkedList->Add("2", 1992);
    linkedList->Add("3", 1993);
    linkedList->Add("4", 1994);
    linkedList->Add("5", 1995);
    linkedList->outputList();

     cout << endl<< "Add Node Head: 0" << endl << endl;
     linkedList->Add("0", 1990);
     linkedList->outputList();
     cout << endl<< "Add Node Tail: 6" << endl << endl;
     linkedList->Add("6", 1996);
     linkedList->outputList();

    cout << endl << "Delete Nodes" << endl << endl;
    linkedList->Delete("1");
    linkedList->Delete("6");
    linkedList->Delete("3");
    linkedList->Delete("4");
    linkedList->Delete("5");

    linkedList->Delete("2");
    linkedList->Delete("0");

    linkedList->outputList();

      cout << endl << "Before Exchange" << endl << endl;
     linkedList->Add("1", 1991);
    linkedList->Add("3", 1993);
    linkedList->Add("5", 1995);
    linkedList->Add("7", 1997);
    linkedList->Add("9", 1999);
    linkedList->outputList();

    cout << endl << "After Exchange of 3 and 7" << endl << endl;
    linkedList->exchangeNodes("3", "7");
    linkedList->outputList();

    cout << endl << "After Exchange of 1 and 9 (Head and Tail)" << endl << endl;
    linkedList->exchangeNodes("1", "9");
    linkedList->outputList();


    delete linkedList;

    string s;
    cout << endl << "Press Enter to Exit";
    getline(cin, s);

    return 0;
}


