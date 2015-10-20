#include <iostream>
#include <string>
#include "LL.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    LL *linkedList = new LL();
    linkedList->Add("hey", 1994);
    linkedList->Add("he", 1993);
    linkedList->Add("heys", 9999);
    linkedList->Add("heyss", 9998);
    Node* head = linkedList->getNote();

    linkedList->outputList();
    return 0;
}
