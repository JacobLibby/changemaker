//
// Created by Jacob on 11/11/2019.
//

#ifndef CHANGEMAKER_LINKEDLIST_H
#define CHANGEMAKER_LINKEDLIST_H


class ListNode {
public:
    // class variables
    int val;
    ListNode* next;

    // constructor
    ListNode(int value, ListNode* nextNode=nullptr) {
        this->val = value;
        this->next = nextNode;
    }
};

// Singly linked list
// Each ListNode stores an integer value as well as a link pointing
// to the next ListNode in the chain
class LinkedList {
private:
    ListNode *head; // pointer to the first ListNode in the Linked List (chain)

public:
    // constructors
    LinkedList();
    LinkedList(LinkedList &toCopy);
    ~LinkedList()=default;

    LinkedList& operator=(LinkedList const &toAssign);

    // helper functions
    int getSize() const;
    bool isEmpty() const;

    // member functions
    void insertAtHead(int value);
    void insertAtTail(int value);
    void removeHead();
    void removeTail();
    int peekHead() const;
    int peekTail() const;
    int at(int index);     // returns the value stored at the index position

    // other functions to implement
    void print();             // print out the values stored in the linked list
    void reverse();           // reverse the ListNodes in the linked list
    bool remove(int target);  // remove the first target value in the linked list
    void clear();             // basically remove all ListNodes and reset the Linked List
    void sort();              // sort the LinkedList in the ascending order based on ListNodes' values
    void merge(LinkedList toMerge); // merge the toMerge LinkedList into the calling LinkedList which should be sorted.
};


#endif //CHANGEMAKER_LINKEDLIST_H
