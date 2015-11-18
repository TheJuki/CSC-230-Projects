/*
File       : title.h
Program    : Program 4 - Binary Search Tree Indexes
Due Date   : December 4, 2015
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
#include <vector>

class TitleIndex
{
    private:
        class Node
        {
            public:
                std::string title;
                int pos;
                Node * left;
                Node * right;
                Node():title("no"), pos(-1), left(NULL), right(NULL) { }
                Node(std::string T, int P): title(T), pos(P), left(NULL), right(NULL) { }
        };
        Node * root;
        unsigned int size;
        void writeFile();
        void readFile();
        void killTree();
        void RealKillTree(Node *&r); // the real recursive routine
        void deleteTitleByTitle(std::string T);
        void deleteTitleByPosition(int P);
        bool delete_node(std::string T); //recursive
    public:
        TitleIndex(): size(0)
        {
            root = NULL;
        }
        TitleIndex(int my_size): size(0)
        {
            root = NULL;
            readFile();
        }
        ~TitleIndex()
        {
            writeFile();
            killTree();
        }
        bool addTitle(std::string T, int P);
        bool findTitle(std::string T, int& P);
        void updateTitle(std::string oldTitle, std::string newTitle);
        void deleteTitle(std::string T, int P);
        int getDeadCount();
        void setDeadCount(int count);
        void getAllTitles();
        int getSize();
        std::vector<int> printAllAlphabetically();
};
#endif // TITLE_H

