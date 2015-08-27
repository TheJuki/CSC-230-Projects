//Justin Kirk
//Practice 7
//main

#include <iostream>
#include "myqueue.h"

using namespace std;

int main()
{
    myqueue meQueue(30);
    for(long i = 3; i <40; i += 4)
        meQueue.enque(i);
    while(!meQueue.isEmpty())
        cout << meQueue.deque() << "\n";
    return(0);
}


