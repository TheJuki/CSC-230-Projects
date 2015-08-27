//Justin Kirk
//Practice 6
//P6_main.cpp

#include <iostream>
#include "mystacks.h"
using namespace std;

int main()
{
    mystacks meStacks(30);
    for(long i = 3; i < 40; i += 4)
        meStacks.push(i);

    while(!meStacks.isEmpty())
        cout << meStacks.pop() << "\n";
    //system("pause"); --Code::Blocks does not have system
    return 0;
}
