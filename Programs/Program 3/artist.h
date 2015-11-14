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
#include <vector>

class ArtistIndex
{
    private:
        class Node
        {
            public:
                std::string artist;
                int pos;
                Node * next;
                Node * prev;
                Node * up;
                Node * down;
                Node():artist("A"), pos(-1), next(NULL), prev(NULL), up(NULL), down(NULL) { }
                Node(std::string A, int P): artist(A), pos(P)
                {
                    next=prev=up=down=NULL;
                }
        };
        Node * head;
        Node * tail;
        unsigned int size;
        void writeSecondary();
        void readSecondary();
        void killList();
        void delete_by_artist(std::string T);
        void delete_by_pos(int P);
    public:
        ArtistIndex(): size(0)
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
        }
        ArtistIndex(int my_size): size(my_size)
        {
            head = new Node(" ", -1);
            tail = new Node("~", -1);
            head->next = tail;
            tail->prev = head;
            readSecondary();
        } // readFile will change size
        ~ArtistIndex()
        {
            writeSecondary();
            killList();
        }
        void addArtist(std::string my_artist, int my_key);
        void updateArtist(std::string old_artist, std::string new_artist, int old_pos);
        int matchArtist(std::string inArtist);
        bool deleteArtist(std::string T, int P);
        std::vector<int> findArtist(std::string inArtist);
        bool matchArtist(std::string inArtist, int &pos);
        void getAllArtists();
};
#endif // ARTIST_H
