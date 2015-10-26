/*
File       : LL.cpp
Program    : Homework 3 Linked List
Due Date   : October 20, 2015
Author     : Justin Kirk
Description: The Linked List (Uses Node)
*/

#include <string>
#include "LL.h"

#include <iostream>

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

void LL::killList()
{
    /*
    if(h != NULL)
    {
        Node * p = h;
        Node * pNext = NULL;
        while (p != NULL)
        {
            pNext = p->next;
            p = p->next;
            delete pNext;
        } // end while
    }
    */
}

bool LL::AddHead(string d, int k)
{
    Node * p = new Node(d, k);
    p->prev = NULL;
    p->next = h;
    h->prev = p;
    h = p;
    size += 1;
    return true;
}
bool LL::AddTail(string d, int k)
{
    Node * p = new Node(d, k);
    p->next = NULL;
    p->prev = t;
    t->next = p;
    t = p;
    size += 1;
    return true;
}

void LL::exchangeNodes(string d1, string d2)
{
    bool isNode1Found = false;
    bool isNode2Found = false;
     Node * p1 = NULL;
     Node * p2 = NULL;

    if(h == NULL)
        cout << "The list is empty" << endl;
    else
    {
        //Find Node 1
        p1 = h;
        while (p1 != NULL)
        {
            if(p1->data == d1)
            {
                isNode1Found = true;
                break;
            }
            p1 = p1->next;
        } // end while

        //Find Node 2
        p2 = h;
        while (p2 != NULL)
        {
            if(p2->data == d2)
            {
                 isNode2Found = true;
                break;
            }
            p2 = p2->next;
        } // end while

        if(isNode1Found && isNode2Found)
        {
            Node * temp = new Node(p1->data, p1->year);
            p1->data = p2->data;
            p1->year = p2->year;
            p2->data = temp->data;
            p2->year = temp->year;
        }
    }
}

void LL::outputList()
{
    Node * p = new Node();

    if(h == NULL)
        cout << "The list is empty" << endl;
    else
    {
        p=h;
        int count = 1;
        while (p != NULL)
        {
            cout << "Node: " << count << " Data: " << p->data << " Year: " << p->year << endl;
            p = p->next;
            ++count;
        } // end while
    }
}

bool LL::DeleteHead()
{
    Node *pDelete = NULL;
    pDelete = h;
    h = pDelete->next;
    delete pDelete;
    --size;
    return true;
}

bool LL::DeleteTail()
{
    Node *pDelete = NULL;
    pDelete = t;
    t = pDelete->prev;
    delete pDelete;
    --size;
    return true;
}

void LL::makeCircular()
{
    if(t != NULL && h != NULL)
    {
        h->prev = t;
        t->next =h;
    }
    isCircular = true;
}

bool LL::Delete(string d)
{
    bool isDeleted = false;

    Node *pHold = NULL;
    Node *pDelete = NULL;

    if (h->data == d)
        return DeleteHead();

    pHold = h;
    pDelete = h->next;

    //walk the list
    while (pDelete != NULL)
    {
        if (pDelete->data == d)
        {
            pHold->next = pDelete->next;

            if (pDelete == t)
            {
                return DeleteTail();
            }
            delete pDelete;
            isDeleted = true;
            --size;
            break;
        }
        pHold = pDelete;
        pDelete = pDelete->next;
    } // end while

    return isDeleted;
}
