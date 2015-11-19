/*
File       : artist.h
Program    : Program 4 - Binary Search Tree Indexes
Due Date   : December 4, 2015
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
                Node * left;
                Node * right;
                Node * up;
                Node * down;
                Node():artist("N"), pos(-1), left(NULL), right(NULL), up(NULL), down(NULL) { }
                Node(std::string T, int P): artist(T), pos(P)
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
        ArtistIndex(): size(0)
        {
            root = NULL;
        }
        ArtistIndex(int my_size): size(my_size)
        {
            root = NULL;
            readFile();
        } // readFile will change size
        ~ArtistIndex()
        {
            writeFile();
            killTree();
        }
        void addArtist(std::string my_artist, int my_key);
        void addArtist(Node *& r, std::string my_Artist, int my_key);
        void updateArtist(std::string old_artist, std::string new_artist, int old_pos);
        int matchArtist(std::string inArtist);
        bool deleteArtist(std::string T, int P);
        std::vector<int> findArtist(std::string inArtist);
        bool matchArtist(std::string inArtist, int &pos);
        void getAllArtists();
};
#endif // ARTIST_H

