#ifndef YEAR_H
#define YEAR_H
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

class YearIndex
{
    private:
        class Node
        {
            public:
                int year;
                int pos;
                Node * left;
                Node * right;
                Node * up;
                Node * down;
                Node():year(-1), pos(-1), left(NULL), right(NULL), up(NULL), down(NULL) { }
                Node(int T, int P): year(T), pos(P)
                {
                    left=right=up=down=NULL;
                }
        };
        Node * root;
        unsigned int size;
        void writeFile();
        void readFile();
        void killTree();
        void RealKillTree(Node *& r);
        void RealKillTreeMiddle(Node *& m);
        void delete_by_artist(std::string T);
        void delete_by_pos(int P);
    public:
        YearIndex(): size(0)
        {
            root = NULL;
        }
        YearIndex(int my_size): size(my_size)
        {
            root = NULL;
            readFile();
        } // readFile will change size
        ~YearIndex()
        {
            writeFile();
            killTree();
        }
        void addYear(Node *& r, int my_Year, int my_key);
        void addYear(int my_Year, int my_key);
        void updateYear(int old_year, int new_year, int old_pos);
        int matchYear(int inYear);
        bool deleteYear(int T, int P);
        std::vector<int> findYear(int inYear);
        bool matchYear(int inYear, int &pos);
        void getAllYears();
};
#endif //YEAR_H


