#include "Node.h"

string Node::getData()
{
    return data;
}
int Node::getYear()
{
    return year;
}

Node* Node::getNext()
{
    return next;
}
Node* Node::getPrev()
{
    return prev;
}
