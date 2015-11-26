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
                int price;
                Node * left;
                Node * right;
                Node():title("no"), pos(-1), price(0), left(NULL), right(NULL) { }
                Node(std::string T, int P, int Pr):title(T), pos(P), price(Pr), left(NULL), right(NULL) { }
        };
        Node * root;
        std::vector<Node*> nodes;
        unsigned int size;
        void writeFile();
        void readFile();
        void killTree();
        void RealKillTree(Node *&r); // the real recursive routine
        void deleteTitleByTitle(std::string T);
        void deleteTitleByPosition(int P);
        Node* deleteTitleByTitle(Node*& r, std::string T);
        bool delete_node(std::string T); //recursive
        void pushNode (Node* r);
        void pushNodes ();
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
        bool addTitle(std::string T, int P, int Pr);
        bool addTitle(Node *& r, std::string my_Title, int my_key, int my_price);
        bool findTitle(std::string T, int& P);
        void updateTitle(std::string oldTitle, std::string newTitle, int newPrice);
        void deleteTitle(std::string T, int P);

        Node* findPred(Node*& r);
        int getDeadCount();
        void setDeadCount(int count);
        void getAllTitles();
        int getSize();
        std::vector<int> printAllAlphabetically();
        std::vector<int> printAllReverseAlphabetically(int userPrice);
        bool findTitleNode(Node *& r, std::string T, int& P);
};
#endif // TITLE_H

