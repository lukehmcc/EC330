//
//  LinkedList.cpp
//
//  Created by Tali Moreshet
//

#include "LinkedList.h"

using namespace std;

/*** Implementation of Node ***/

// Constructor
Node::Node(int data) {
  this->data = data;
  this->next = nullptr;
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
    head = newNode;
    return;
  }
  Node *current = head;
  // iterate to last node
  while (current->next != nullptr) {
    current = current->next;
  }
  // insert new node at the end.
  current->next = newNode;
}

// remove node from tail of list, return its data
int LinkedList::removeFromTail() {
  Node *current = head;
  // check if empty
  if (current == nullptr) {
    cout << "Error: cannot remove empty tail" << endl;
    return -1;
  }
  // check if there is only 1 value
  if (current->next == nullptr) {
    int tmp = current->data;
    delete current->next;
    head = nullptr;
    return tmp;
  }

  // now iterate through
  while (current->next->next != nullptr) {
    current = current->next;
  }
  int tmp = current->next->data;
  delete current->next->next;
  current->next = nullptr;
  return tmp;
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

// constrcutor
StackFromList::StackFromList() {
  // init
  list = new LinkedList();
}

// desctructor
StackFromList::~StackFromList() {
  // nuke that list
  delete list;
}

// insert to top of stack
void StackFromList::push(int data) { // insert to top of the stack
  list->insertToHead(data);
}

// take off the top of the stack
int StackFromList::pop() {
  // return that head
  return list->removeFromHead();
}

// take off the top of the stack
bool StackFromList::isEmpty() {
  if (list->getSize() == 0) {
    return true;
  } else {
    return false;
  }
}

QueueFromList::QueueFromList() {
  // init
  list = new LinkedList();
}
QueueFromList::~QueueFromList() {
  // nuke that list
  delete list;
}
void QueueFromList::enqueue(int i) {
  // insert to head
  list->insertToHead(i);
}
int QueueFromList::dequeue() {
  // remove from tail
  return list->removeFromTail();
}
bool QueueFromList::isEmpty() {
  // get size
  if (list->getSize() == 0) {
    return true;
  } else {
    return false;
  }
}
void QueueFromList::print() { list->print(); }
