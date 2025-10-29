//
//  LinkedList.cpp
//
//  Created by Luke McCarthy
//

#include "LinkedList.h"

using namespace std;

/*** Implementation of Node ***/

// Constructor
Node::Node(int data) {
  this->data = data;
  this->next = nullptr;
  this->prev = nullptr;
}

// Print node's data value
void Node::print() { cout << data << " "; }

/*** Implementation of linked list ***/

// Constructor
LinkedList::LinkedList() { head = nullptr; }

// Destructor
LinkedList::~LinkedList() {
  Node *current = head;
  while (current) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

// insert node with data to tail of list
void LinkedList::insertToTail(int data) {
  // define new node
  Node *newNode = new Node(data);

  // check if empty
  if (head == nullptr) {
    head = tail = newNode;
    return;
  }
  tail->next = newNode;
  newNode->prev = tail;
  tail = tail->next;
}

// remove node from tail of list, return its data
int LinkedList::removeFromTail() {
  // check if empty
  if (tail == nullptr) {
    cout << "Error: cannot remove empty tail" << endl;
    return -1;
  }
  // check if single node
  if (head == tail) {
    int data = head->data;
    delete head;
    head = tail = nullptr;
    return data;
  }
  Node *current = tail;
  int data = current->data;
  tail = tail->prev;
  tail->next = nullptr;
  delete current;
  return data;
}

// insert node with data to head of list
void LinkedList::insertToHead(int data) {
  Node *newNode = new Node(data);

  if (head == nullptr) // empty list
  {
    head = newNode;
    newNode->next = nullptr;
  } else {
    newNode->next = head;
    head = newNode;
  }

  return;
}

// remove node from head of list, return its data
int LinkedList::removeFromHead() {
  if (head == nullptr) {
    cout << "Error: cannot pull from empty linked list" << endl;
    return -1;
  }
  int tmp = head->data;
  head = head->next;
  return tmp;
}

int LinkedList::getSize() {
  int size = 0;
  Node *current = head;
  // iterate through and inc counter
  while (current) {
    current = current->next;
    size++;
  }
  return size;
}

// Print linked list data
void LinkedList::print() {
  if (head == nullptr) {
    cout << "Linked list is empty" << endl;
    ;
    return;
  }

  head->print();

  if (head->next == nullptr) {
    cout << endl;
    return;
  }

  Node *currNode = head->next;
  Node *prevNode = head;

  while (currNode->next != nullptr) {
    currNode->print();
    prevNode = currNode;
    currNode = currNode->next;
  }

  currNode->print();
  cout << endl;
}

// Swap two nodes
void LinkedList::swap(Node *node1, Node *node2) {
  // make sure the nodes exist and aren't the same
  if (!node1 || !node2 || node1 == node2)
    return;

  // swap tail & head early in case adjacent
  if (tail == node1)
    tail = node2;
  else if (tail == node2)
    tail = node1;
  if (head == node1)
    head = node2;
  else if (head == node2)
    head = node1;

  // check if they are neighbors 6 instead of 8 pointers to deal with
  if (node1->next == node2) {
    Node *n1 = node1;
    Node *n2 = node2;
    Node *n1p = node1->prev;
    Node *n2n = node2->next;

    if (n1p)
      n1p->next = n2;

    // swap the internal pointers
    n2->prev = n1p;
    n2->next = n1;
    n1->prev = n2;
    n1->next = n2n;

    if (n2n)
      n2n->prev = n1;

    // return
    return;
  } else if (node2->next == node1) {
    // same as previous just flipped
    Node *n2 = node2;
    Node *n1 = node1;
    Node *n2p = node2->prev;
    Node *n1n = node1->next;

    if (n2p)
      n2p->next = n1;

    // swap the internal pointers
    n1->prev = n2p;
    n1->next = n2;
    n2->prev = n1;
    n2->next = n1n;

    if (n1n)
      n1n->prev = n2;
    return;
  }

  // save the neighbors
  Node *node1prev = node1->prev;
  Node *node1next = node1->next;
  Node *node2prev = node2->prev;
  Node *node2next = node2->next;

  // recconect neighbor nodes
  if (node1prev)
    node1prev->next = node2;
  if (node1next)
    node1next->prev = node2;
  if (node2prev)
    node2prev->next = node1;
  if (node2next)
    node2next->prev = node1;

  // swap internal routing
  node1->prev = node2prev;
  node1->next = node2next;
  node2->prev = node1prev;
  node2->next = node1next;
  // validate integrity
  Node *cur = head;
  while (cur && cur->next) {
    // cout << cur->data << " -> ";
    if (cur->next->prev != cur) {
      // handle error
      cout << "Your link is borked bruv" << endl;
      return;
    }
    cur = cur->next;
  }
  cur = tail;
  while (cur && cur->prev) {
    // cout << cur->data << " <- ";
    if (cur->prev->next != cur) {
      // handle error
      cout << "Take a gander at your links my good fellow" << endl;
      return;
    }
    cur = cur->prev;
  }
  // cout << cur->data << endl;
}

// removes node and returns it's value
int LinkedList::removeNode(Node *node) {
  // check for nullptr
  if (node == nullptr) {
    cout << "Error: cannot remove empty node" << endl;
    return -1;
  }
  // make sure it's not the head or tail and use premade functions for that
  if (node == tail) {
    return removeFromTail();
  } else if (node == head) {
    return removeFromHead();
  }
  // if it's actually in the middle of the list, do the shenanigans
  Node *current = node;
  Node *prev = node->prev;
  Node *next = node->next;
  prev->next = next;
  next->prev = prev;
  int data = current->data;
  delete current;
  return data;
}

// sorts the linked list such that all negative integers are to the left of
// zeros
void LinkedList::zeroSort() {
  Node *current = head;
  // keeps track of how many times the array has been touched to get around the
  // "treadmill" problem
  int iterator = 0;
  int size = getSize();
  while (current != nullptr && iterator < size) {
    Node *sacrifice = current;
    current = current->next;
    iterator++;
    // Now if it's smaller than zero send it to the front
    if (sacrifice != head && sacrifice->data < 0) {
      insertToHead(removeNode(sacrifice));
      // and if it's bigger than 0 send it to the back
    } else if (sacrifice != tail && sacrifice->data > 0) {
      insertToTail(removeNode(sacrifice));
    } else {
      // it's a zero, do nothing
    }
  }
}

Node *LinkedList::findFirst(int val) {
  for (Node *current = head; current; current = current->next)
    if (current->data == val) {
      return current;
    }
  return nullptr;
}
