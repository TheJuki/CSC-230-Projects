#ifndef TITLE_H
#define TITLE_H
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cctype>

class Title{

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
        Title()
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
            size = 0;
        }
        Title(unsigned int InSize):size(InSize)
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
            readFile();
        }
        ~Title() {writeFile(); killList();}

        bool SetTitlePos(std::string T, int P);
        bool findTitle(std::string T, int& P);
        void changeTitle(std::string oldTitle, std::string newTitle);
        void deleteTitle(std::string T, int P);
};
#endif // TITLE_H
