//Justin Kirk
//Practice 6
//mystacks.h 

#ifndef MYSTACKS_H
#define MYSTACKS_H
class mystacks
{
    private:
        int top, size;
        long array[100];
    public:
        mystacks() { top = -1; size = 20;}
        mystacks(unsigned int max_size)
        {
            top = -1;
            if(max_size >= 100)
                size = 100;
            else if(max_size <= 2)
                size = 10;
            else
                size = int(max_size);
        }
        bool push(long item);
        long pop();
        bool isEmpty();
        bool isFull();
};
#endif // MYSTACKS_H
