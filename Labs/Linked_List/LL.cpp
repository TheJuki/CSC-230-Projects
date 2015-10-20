#include <string>
#include "LL.h"


#include <iostream>


using namespace std;

 Node* LL::getNote()
 {
     return h;
 }

bool LL::Add(string d, int k)
{
    if(h==NULL) // empty
    {
        Node * p = new Node(d, k);
        h = t = p;
        size = 1;
        return true;
    }
    else if(h->data>d)
        return AddHead(d,k);
    else if(t->data<d)
        return AddTail(d,k);
    else
        return AddIn(d,k);
}

bool LL::AddIn(string d, int k)
{
    Node * wp = h->next;
    if(h->data==d)
        return false;
    if(t->data==d)
        return false;
     while(wp != NULL)
    {
        if(wp->data==d)
            return false;
        if(wp->data>d)
        {
            //Node * p = Node(d,k);
            //new not added by Whitson - BONUS
            Node * p = new Node(d,k);
            p->prev = wp->prev;
            p->next = wp;
            wp->prev->next=p;
            wp->prev=p;
            size += 1;
            return true;
        }
        wp=wp->next;
    }

    return false;
}

void LL::killList(){}
//Works
bool LL::AddHead(string d, int k)
{
    Node * p = new Node(d, k);
    p->next = h;
    h = p;
    size += 1;
     //cout << h->getYear() << endl;
    return false;
}
bool LL::AddTail(string d, int k)
{
    Node * p = new Node(d, k);
    p->prev = t;
    t = p;
    size += 1;
    //cout << t->getYear() << endl;
    return false;
}

string LL::outputList()
{
     Node * p = new Node();
     p=h;
    while(p->next != NULL)
    {
        cout << p->getData() << " " << p->getYear() << endl;
        p = p->next;
    }
}

bool LL::Delete(string d){return false;}
