#include "Title.h"
using namespace std;

void Title::killList()
{
    Node * wp = head;
    Node * hold;

    while(wp != NILL)
    {
        hold = wp;
        wp = wp->next;
        delete hold;
    } //end while
    head = tail = NULL;
    size = 0;
}

void Title::writeFile()
{
    Node * wp = head->next;
    ofstream fout("title_index.txt");
    fout << size << endl;
    while(wp != tail)
    {
        fout << wp->title << " " << wp->pos << endl;
        wp = wp->next;
    } //end while
    fout.close;
}

void Title::readFile()
{
    Node * wp = head;
    Node * hold;
    string newTitle;
    int newPos;

    ifstream fin("title_index.txt");
    fin >> size;
    wp = head;
    for(unsigned int i = 0; i < size; ++i)
    {
        fin >> newTitle >> newPos;
        hold = new Node(newTitle, newPos);
        wp->next = hold;
        hold->prev = wp;
        tail->prev = hold;
        hold->next = tail;
        wp = wp->next;
    } // end for
    fin.close();
}

void Title::deleteTitleByTitle(string T)
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
    return;
}



