#include "LinkedList.h"
#include <iostream>
using namespace std;

// CONSTRUCTORS //
// default constructor
LinkedList::LinkedList() {
    this->head = nullptr;
}

// copy constructor (deep copy)
LinkedList::LinkedList(LinkedList &toCopy){
    // is Empty?
    if (isEmpty()){
        this->head = nullptr;
    }
    else {
        ListNode *cursor1 = nullptr;
        ListNode *cursor2 = toCopy.head;

        this->head = new ListNode(cursor2->val);
        cursor1 = this->head;
        cursor2 = cursor2->next;
        while (cursor2 != nullptr) { // copies one node at a time
            cursor1->next = new ListNode(cursor2->val);
            cursor1 = cursor1->next;
            cursor2 = cursor2->next;
        }
    }
}

// operator overload ( = )
LinkedList& LinkedList::operator=(LinkedList const &toAssign) {
    if (this != &toAssign){
        this->head = toAssign.head;
    }
    return *this;
}

// HELPER FUNCTIONS //
// getSize
int LinkedList::getSize() const{
    int counter = 0;
    if (!isEmpty()){
        ListNode *curr = this->head;
        counter++;
        while (curr->next != nullptr){
            curr = curr->next;
            counter++;
        }
    }
    return counter;
}

// isEmpty
bool LinkedList::isEmpty() const{
    return this->head == nullptr;
}

// MEMBER FUNCTIONS //
// insertAtHead
void LinkedList::insertAtHead(int value) {
    ListNode *newNode = new ListNode(value);
    if (!isEmpty()){
        newNode->next = this->head;
    }
    this->head = newNode;
}

// insertAtTail
void LinkedList::insertAtTail(int value) {
    ListNode *newNode = new ListNode(value);
    if (isEmpty()){
        this->head = newNode;
    }
    else {
        ListNode *curr = this->head;
        while (curr->next != nullptr){ /////////////////// while (curr != nullptr)
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

// removeHead
void LinkedList::removeHead() {
    if (isEmpty()) {
        throw runtime_error("LinkedList::removeHead, Linked List is Empty");
    }
    this->head = this->head->next;
}

// removeTail
void LinkedList::removeTail() {
    if (isEmpty()){
        throw runtime_error("LinkedList::removeTail, Linked List is Empty");
    }
    ListNode *curr = this->head; // pointer at nth node
    ListNode *prev = nullptr; // pointer at (n-1)th node
    while (curr->next != nullptr){ // while curr != tail
        prev = curr;
        curr = curr->next;
    }
    if (this->head->next == nullptr){ // if one node linked list
        this->head = nullptr;
    }
    else{
        prev->next = curr->next;
    }
}

// peekHead
int LinkedList::peekHead() const{
    if (isEmpty()){
        throw runtime_error("LinkedList::peekHead, Linked List is Empty");
    }
    return this->head->val;
}

// peekTail
int LinkedList::peekTail() const{
    if (isEmpty()) {
        throw runtime_error("LinkedList::peekTail, Linked List is Empty");
    }
    ListNode *curr = this->head;
    while (curr->next != nullptr){
        curr = curr->next;
    }
    return curr->val;
}

// at
int LinkedList::at(int index) {
    if (isEmpty()){
        throw runtime_error("LinkedList::at, Linked List is Empty");
    }
    if (index < 0){
        throw runtime_error("LinkedList::at, index out of scope [ index < 0 ]");
    }
    ListNode *curr = this->head;
    int counter = 0;
    while (counter < index){
        if (curr->next == nullptr){
            throw runtime_error("LinkedList::at, index out of scope [ index > size of LinkedList ]");
        }
        curr = curr->next;
        counter++;
    }
    return curr->val;
}

// OTHER FUNCTIONS //
// print
void LinkedList::print(){
    if (!isEmpty()) {
        ListNode *curr = this->head;
        while (curr != nullptr) {
            cout << curr->val << "->";
            curr = curr->next;
        }
    }
    cout << "nullptr" << endl;

}

// reverse
void LinkedList::reverse() {
    ListNode *curr = this->head;
    ListNode *reversePointer = this->head;
    ListNode *firstNode = this->head;
    while (reversePointer->next != nullptr){ // move reversePointer to last node of linked list
        reversePointer = reversePointer->next;
    }
    this->head = reversePointer;
    while (reversePointer != firstNode){
        while (curr->next != reversePointer){
            curr = curr->next;
        }
        reversePointer->next = curr;
        reversePointer = reversePointer->next;
        if (reversePointer == firstNode){
            reversePointer->next = nullptr;
        }
        else {
            curr = firstNode;
        }
    }
}

// remove
bool LinkedList::remove(int target){
    if (isEmpty()){
        return false;
    }
    ListNode *curr = this->head;
    if (curr->val == target){ // if first node == target
        if (curr->next != nullptr){
            this->head = curr->next;
        }
        else { // curr->next == nullptr)
            this->head = nullptr;
        }
        return true;
    }
    while (curr != nullptr){ // checking each node in linked list
        if (curr->next->val == target){ // if next node == target
            curr->next = curr->next->next; // remove next node
            return true;
        }
        curr = curr->next;
    }
    return false; // target not found
}

// clear
void LinkedList::clear(){
    this->head = nullptr;
}

// sort
void LinkedList::sort() {
    if (!isEmpty()) {
        ListNode *prev = this->head;
        ListNode *curr1 = this->head;
        ListNode *curr2 = this->head->next;

        while (curr2 != nullptr) { //curr2->next != nullptr
            if (curr1->val > curr2->val) {
                curr1->next = curr2->next;
                curr2->next = curr1;
                if (curr1 != prev) {
                    prev->next = curr2;
                }
                if (this->head == curr1) {
                    this->head = curr2;
                }
                prev = this->head;
                curr1 = this->head;
                curr2 = curr1->next;
                if (curr1->val > curr2->val) {
                    curr1->next = curr2->next;
                    curr2->next = curr1;
                    if (curr1 != prev) {
                        prev->next = curr2;
                    }
                    if (this->head == curr1) {
                        this->head = curr2;
                    }
                    prev = this->head;
                    curr1 = this->head;
                    curr2 = curr1->next;
                }
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
            if (curr1 != this->head->next) {
                prev = prev->next;
            }
        }
    }
}

// merge
void LinkedList::merge(LinkedList toMerge){
    ListNode *curr = toMerge.head;
    while (curr != nullptr){ // combining the two linked lists
        this->insertAtTail(curr->val);
        curr = curr->next;
    }
    this->sort(); // sorting the combined linkedlist
}