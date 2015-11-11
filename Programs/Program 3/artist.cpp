/*
File       : artist.cpp
Program    : Program 3 - Sorted Double Linked-List
Due Date   : November 16, 2015
Author     : Justin Kirk
Description: Artist - secondary index
*/

#include "artist.h"


void ArtistIndex::addArtist(std::string myArtist, int myKey)
{

}
void ArtistIndex::updateArtist(std::string old_artist, std::string new_artist)
{

}
void ArtistIndex::writeSecondary()
{

}
void ArtistIndex::readSecondary()
{

}
int * ArtistIndex::findArtist(std::string inArtist)
{
    static int emptyArray[1];
    emptyArray[0] = 0;
    return emptyArray;
}
bool ArtistIndex::matchArtist(std::string inArtist, int pos[])
{
    return false;
}

bool ArtistIndex::deleteArtist(std::string inArtist, int pos)
{
    return false;
}

void ArtistIndex::killList()
{
    Node * wp = head;
    Node * wsp = NULL;
    Node * hold;
    while(wp != NULL)
    {
        if(wp->down != NULL)
        {
            wsp = wp->down;
            while(wsp->down != NULL)
                wsp = wsp->down;
            while(wsp->up != NULL)
            {
                hold = wsp;
                wsp = wsp->up;
                delete hold;
            }
        }
        hold = wp;
        wp = wp->next;
        delete hold;
    }
    return;
}

