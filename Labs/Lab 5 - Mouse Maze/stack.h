#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

class Stack {
private:
      int top;
      int capacity;
      int *x;
      int *y;
public:
      Stack(int capacity) {
            if (capacity <= 0)
                  throw string("Stack's capacity must be positive");
            x = new int[capacity];
            y = new int[capacity];
            this->capacity = capacity;
            top = -1;
      }

      void pushes(int row, int column) {
            if (top == capacity)
                  throw string("Stack is at max capacity");
            top++;
            x[top] = row;
            y[top] = column;
      }

      int peek_x() {
            if (top == -1)
                  throw string("Stack is empty");
            return x[top];
      }
      int peek_y() {
            if (top == -1)
                  throw string("Stack is empty");
            return y[top];
      }

      void pops() {
            if (top == -1)
                  throw string("Stack is empty");
            top--;
      }

      bool isEmpty() {
            return (top == -1);
      }

      ~Stack() {
            delete[] x;
            delete[] y;
      }
};

#endif // STACK_H
