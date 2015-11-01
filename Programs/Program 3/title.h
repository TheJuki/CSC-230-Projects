/*
File       : title.h
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Header for title.cpp
*/

#ifndef TITLE_H
#define TITLE_H
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cctype>

class TitleIndex{

private:
    class Node {

    public:
        std::string title;
        int pos;
        Node * next;
        Node * prev;
        Node():title("no"), pos(-1), next(NULL), prev(NULL) {}
        Node(std::string T, int P): title(T), pos(P), next(NULL), prev(NULL) {}
    };

    Node * head;
    Node * tail;
    unsigned int size;

    void writeFile();
    void readFile();
    void killList();
    void deleteTitleByTitle(std::string T);
    void deleteTitleByPosition(int P);

    public:
        TitleIndex()
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
            size = -1;
        }
        TitleIndex(unsigned int InSize):size(InSize)
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
            readFile();
        }
        ~TitleIndex() {writeFile(); killList();}

        bool addTitle(std::string T, int P);
        bool findTitle(std::string T, int& P);
        void updateTitle(std::string oldTitle, std::string newTitle);
        void deleteTitle(std::string T, int P);
        int getDeadCount();
        void setDeadCount(int count);
        void getAllTitles();
        int getSize();
};
#endif // TITLE_H