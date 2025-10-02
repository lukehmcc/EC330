//
//  LinkedList.h
//  Linked_List_Stack_Queue
//
//  Created by Tali Moreshet
//
//  This is an implementation of a Linked List class, which is made up of Nodes.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using namespace std;

class Node {
public:
  Node(int data); // constructor
  int data;       // node data, doubles as key
  Node *next;     // node next pointer
  void print();   // prints data value
};

class LinkedList {
public:
  LinkedList();                // constructor
  ~LinkedList();               // destructor
  void insertToTail(int data); // insert node with data to tail of list
  int removeFromTail();        // remove node from tail of list, return its data
  void insertToHead(int data); // insert node with data to head of list
  int removeFromHead();        // remove node from head of list, return its data
  int getSize();               // returns size of linked list
  void print();                // prints linked list data
private:
  Node *head; // head of list
};

class StackFromList {
public:
  StackFromList();     // constrcutor
  ~StackFromList();    // desctructor
  void push(int data); // insert to top of stack
  int pop();           // take off the top of the stack
  bool isEmpty();      // check if anything is on the stack
private:
  LinkedList *list; // internal linked list to keep track of state
};

#endif /* LinkedList_h */
