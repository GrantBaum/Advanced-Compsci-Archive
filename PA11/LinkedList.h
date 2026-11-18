#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Node structure for the Linked List
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void append(int data);
    void prepend(int data);
    bool removeHead();
    bool remove(int data);
    void display() const;
    void insertAfter(int after, int data);
    void reverse();

private:
    Node* head;
};

#endif // LINKEDLIST_H