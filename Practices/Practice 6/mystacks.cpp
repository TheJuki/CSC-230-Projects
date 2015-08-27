//Justin Kirk
//Practice 6
//mystacks.cpp

#include "mystacks.h"
bool mystacks::push(long item)
{
    if(isFull())
        return false;
    top++;
    array[top] = item;
    return true;
}

long mystacks::pop()
{
    if(isEmpty())
        return (-100);
    long hold = array[top];
    top--;
    return hold;
}

bool mystacks::isEmpty()
{
    return (top == -1);
}

bool mystacks::isFull()
{
    return (top == (size-1));
}

