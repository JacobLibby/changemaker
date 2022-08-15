#include "LinkedList.h"

class Stack {
private:
    LinkedList theList;
    int size;

public:
    Stack();
    Stack(Stack& toCopy);
    ~Stack();

    int getSize() const;        // returns the number of elements in the stack
    bool isEmpty() const; // returns if the stack is empty
    int getTop() const;   // returns the top element stored in the stack
    void push(int value); // push an element into the stack
    void pop();           // pop an element into the stack
};
