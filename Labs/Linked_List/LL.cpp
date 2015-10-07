#include <string>
#include "LL.h"

using namespace std;

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
bool LL::AddHead(string d, int k){return false;}
bool LL::AddTail(string d, int k){return false;}
bool LL::Delete(string d){return false;}
