//Justin Kirk
//Practice 7
//myqueue.cpp

#include "myqueue.h"

bool myqueue::enque(long item)
{
    if(isFull())
        return false;
    tail = (tail+ 1) % max_size;
    array[tail] = item;
    size++;
    return true;
}

long myqueue::deque()
{
    if(isEmpty())
        return(-100);
    long hold = array[head];
    head = (head + 1) % max_size;
    size--;
    return hold;
}

bool myqueue::isEmpty()
{
    return (size == 0);
}

bool myqueue::isFull()
{
    return (size == (max_size-1));
}
