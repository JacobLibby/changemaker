#include <stdexcept>
#include "Stack.h"
using namespace std;

Stack::Stack() {
    this->theList.clear();
    this->size = 0;
}

Stack::Stack(Stack& toCopy) {
    this->theList.clear();
    while (!toCopy.isEmpty()){
        this->theList.insertAtHead(toCopy.getTop());
    }
    this->size = toCopy.size;
}

Stack::~Stack() {
    while (!this->theList.isEmpty()){
        this->theList.removeHead();
    }
    size = 0 ;
}

int Stack::getSize() const {
    return this->theList.getSize();
}

bool Stack::isEmpty() const {
    return theList.isEmpty();
}

int Stack::getTop() const{
    if (this->theList.isEmpty())
        throw runtime_error("Stack::getTop, stack is empty");
    return theList.peekHead();
}


void Stack::push(int value) {
    this->theList.insertAtHead(value);
    this->size++;
}

void Stack::pop() {
    if (this->theList.isEmpty()){
        throw runtime_error("Stack::pop, stack is empty");
    }
    else {
        this->theList.removeHead();
        this->size--;
    }
}