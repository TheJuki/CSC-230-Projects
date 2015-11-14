/*
File       : title.cpp
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Code for title data
*/

#include "title.h"

using namespace std;

void TitleIndex::killList()
{
    Node * wp = head;
    Node * hold;

    while(wp != NULL)
    {
        hold = wp;
        wp = wp->next;
        delete hold;
    } //end while
    head = tail = NULL;
    size = 0;
}

void TitleIndex::getAllTitles()
{
     Node * wp = head->next;

    cout << size << endl;
    while(wp != NULL)
    {
        cout << wp->title << " " << wp->pos << endl;
        wp = wp->next;
    } //end while
}


void TitleIndex::writeFile()
{
    Node * wp = head->next;
    ofstream fout("title_index.txt");
    fout << size << endl;
    while(wp != NULL)
    {
        fout << wp->title << " " << wp->pos << endl;
        wp = wp->next;
    } //end while
    fout.close();
}

void TitleIndex::readFile()
{
    string newTitle;
    int newPos;
    int numOfTitles = 0;

    ifstream fin("title_index.txt");
    fin >> numOfTitles;
    for(unsigned int i = 0; i < numOfTitles+2; ++i)
    {
        fin >> newTitle >> newPos;
        addTitle(newTitle, newPos);
    } // end for
    fin.close();
}

void TitleIndex::deleteTitleByTitle(string T)
{
    Node * wp = head->next;
    while(wp != tail)
    {
        if(wp->title == T)
        {
            wp->prev->next = wp->next;
            wp->next->prev = wp->prev;
            delete wp;
            size--;
            return;
        }
        else
        {
            wp = wp->next;
        }
    } //end while
     if(wp == tail && wp->title == T)
    {
        Node *pDelete = NULL;
        pDelete = tail;
        tail = pDelete->prev;
        delete pDelete;
        --size;
    }
    return;
}

std::vector<int> TitleIndex::printAllAlphabetically()
{
    Node * wp = head->next;

    std::vector<int> myVector;
    while(wp != NULL)
    {
        myVector.push_back(wp->pos);
        wp =  wp->next;
    } // end while

    return myVector;
}
void TitleIndex::deleteTitleByPosition(int P)
{
    Node * wp = head->next;
    while(wp != tail)
    {
        if(wp->pos == P)
        {
            wp->prev->next = wp->next;
            wp->next->prev = wp->prev;
            delete wp;
            size--;
            return;
        }
        else
        {
            wp = wp->next;
        }
    } //end while
    if(wp == tail && wp->pos == P)
    {
        Node *pDelete = NULL;
        pDelete = tail;
        tail = pDelete->prev;
        delete pDelete;
        --size;
    }
}

void TitleIndex::deleteTitle(string T, int P)
{
    if(P>0)
        deleteTitleByPosition(P);
    if(T.length() > 1)
        deleteTitleByTitle(T);
    return;
}

bool TitleIndex::addTitle(string T, int P)
{
    int holdPos = 0;
    if(!findTitle(T, holdPos))
    {
        if(head->title>T)
        {
            Node * wp = new Node(T, P);
            wp->prev = NULL;
            wp->next = head;
            head->next = wp;
            head = wp;
            size += 1;
        }
        else if(tail->title<T)
        {
            Node * wp = new Node(T, P);
            wp->next = NULL;
            wp->prev = tail;
            tail->prev = wp;
            tail = wp;
            size += 1;
        }
        else
        {
            Node * wp = head->next;
            while(wp != NULL)
            {
                if(wp->title>T)
                {
                    Node * wp2 = new Node(T,P);
                    wp2->prev = wp->prev;
                    wp2->next = wp;
                    wp->prev->next=wp2;
                    wp->prev=wp2;
                    size += 1;
                    return true;
                }
                wp=wp->next;
            }
        }
        return true;
    }
    return false;
}

bool TitleIndex::findTitle(string T, int& P)
{
    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->title == T)
        {
            P = wp->pos;
            return true;
        }
         wp = wp->next;
    } // end while
      P = 0;
      return false;
}

void TitleIndex::updateTitle(string oldtitle, string newTitle)
{
    Node * wp = head->next;

    while(wp != NULL)
    {
        if(wp->title == oldtitle)
        {
            wp->title = newTitle;
            return;
        }
        wp = wp->next;
    } // end while
}

int TitleIndex::getSize()
{
    return size;
}

