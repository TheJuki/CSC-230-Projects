/*
File       : artist.cpp
Program    : Program 1 - Array Based Indexes
Due Date   : null
Author     : Justin Kirk
Description: Code for artist data
*/

#include "artist.h"

bool myqueue::enque(long item)
{
    if(isFull())
        return false;
    tail = (tail+ 1) % max_size;
    array[tail] = item;
    size++;
    return true;
}
