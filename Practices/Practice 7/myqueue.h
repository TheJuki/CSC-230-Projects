//Justin Kirk
//Practice 7
//myqueue.h

#ifndef MYQUEUE
#define MYQUEUE
class myqueue
{
private:
    int head, tail, max_size, size;
    long array[100];

public:
    myqueue() {head = 0; tail = -1; size = 0; max_size = 20;}
    myqueue(unsigned int input_size)
    {
        tail = -1;
        head = 0;
        size = 0;
        if (input_size >= 100)
            max_size = 100;
        else if(input_size <= 2)
            max_size = 10;
        else
            max_size = int(input_size);
    }

    bool enque(long item);
    long deque();
    bool isEmpty();
    bool isFull();
};
#endif // MYQUEUE
