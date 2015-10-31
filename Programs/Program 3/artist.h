/*
File       : artist.h
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Header for artist.cpp
*/

#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

class ArtistIndex
{
private:
     class A_Node {

    public:
        std::string artist;
        int pos;
        A_Node * next;
        A_Node * prev;
        A_Node():artist("no"), pos(-1), next(NULL), prev(NULL) {}
        A_Node(std::string T, int P): artist(T), pos(P), next(NULL), prev(NULL) {}
    };
    A_Node * head;
    A_Node * tail;
    int size;

public:
    ArtistIndex(): size(0)
    {
        head = new A_Node(" ", -1);
        tail = new A_Node("~", -1);
        head->next = tail;
        tail->prev = head;
    }
    ArtistIndex(int InSize):size(InSize)
        {
            head = new A_Node(" ", -1);
            tail = new A_Node("~", -1);
            head->next = tail;
            tail->prev = head;
            readSecondary();
        }
    ~ArtistIndex() {kill_A_List();}

    std::string getArtist(int pos) const;
    void addArtist(std::string myArtist, int myKey);
    void updateArtist(std::string old_artist, std::string new_artist);
    void writeSecondary();
    void readSecondary();
    int * findArtist(std::string inArtist);
    bool matchArtist(std::string inArtist, int pos[]);
    void kill_A_List();
    bool deleteArtist(std::string inArtist, int pos);
};
#endif // ARTIST_H
