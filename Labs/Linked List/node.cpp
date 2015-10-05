#include <string>

class Node
{ friend class LL;
private:
    std::string data;
    int year;
    Node* next;
    Node* prev;

public:
    Node():data(""), year(-1) {next = prev = NULL;}
    Node(std::string str, int y):year(y), data(str)
    {
        next = prev = NULL;
    }
};
