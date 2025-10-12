//
//  LinkedList.h
//  Linked_List
//
//  Created by Tali Moreshet
//
//  This is an implementation of an unordered Doubly Linked List class, which is
//  made up of Nodes.

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using namespace std;

class Node {
public:
  Node(int data); // constructor
  int data;       // node data, doubles as key
  Node *next;     // node next pointer
  Node *prev;     // node previous pointer
  void print();   // prints data value
};

class LinkedList {
public:
  LinkedList();                // constructor
  ~LinkedList();               // destructor
  void insertToTail(int data); // insert node with data to tail of list
  int removeFromTail();        // remove node from tail of list, return its data
  void insertToHead(int data); // insert node with data to head
  int removeFromHead();        // remove node from head of list, return its data
  int getSize();               // returns size of linked list
  void swap(Node *node1, Node *node2); // swaps the location of the two provided
                                       // nodes in the linked list
  int removeNode(Node *node);          // Deletes the node
  void zeroSort(); // sorts the linked list such that all negative integers are
                   // located
                   //  on the left of the list, all positive integers on the
                   //  right of the list, and all zeros (if any) in the middle.
  Node *findFirst(int val); // finds first with that data value
  void print();             // prints linked list data
  Node *head;               // head of list
  Node *tail;               // tail of list
};

#endif /* LinkedList_h */
