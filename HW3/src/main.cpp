//
//  main.cpp
//  Linked_List_Stack_Queue
//
//  Created by Tali Moreshet
//

#include "LinkedList.h"

using namespace std;

int main(int argc, const char *argv[]) {

  /*** For part (a): Testing of linked list: ***/
  cout << "*** Int linked list: ***" << endl;
  LinkedList myLL = LinkedList();

  myLL.insertToTail(1);
  myLL.insertToTail(2);
  myLL.insertToTail(3);
  myLL.insertToTail(4);
  myLL.insertToTail(5);

  cout << "The size of the linked list is " << myLL.getSize() << endl;
  cout << "Content of linked list: ";
  myLL.print();

  int element = myLL.removeFromHead();

  cout << "Removed " << element << " from head. The size of the linked list is "
       << myLL.getSize() << endl;
  cout << "Content of linked list: ";
  myLL.print();

  element = myLL.removeFromTail();
  cout << "Removed " << element << " from tail. The size of the linked list is "
       << myLL.getSize() << endl;
  cout << "Content of linked list: ";
  myLL.print();

  myLL.insertToHead(0);
  cout << "Inserted 0 to head. The size of the linked list is "
       << myLL.getSize() << endl;
  cout << "Content of linked list: ";
  myLL.print();

  /*** For part (b): Testing of stack: ***/
  cout << endl << endl << "*** Stack: ***" << endl;
  StackFromList myStack;

  cout << "Pushing to the stack: 1 2 3 4" << endl;

  myStack.push(1);
  myStack.push(2);
  myStack.push(3);
  myStack.push(4);

  cout << "The top of the stack was " << myStack.pop() << endl;
  cout << "The top of the stack was " << myStack.pop() << endl;

  cout << "Pushing to the stack: 5 6" << endl;

  myStack.push(5);
  myStack.push(6);

  cout << "The stack is ";
  if (!myStack.isEmpty())
    cout << "not ";
  cout << "empty" << endl;

  cout << "The top of the stack was " << myStack.pop() << endl;
  cout << "The top of the stack was " << myStack.pop() << endl;
  cout << "The top of the stack was " << myStack.pop() << endl;
  cout << "The top of the stack was " << myStack.pop() << endl;

  cout << "The stack is ";
  if (!myStack.isEmpty())
    cout << "not ";
  cout << "empty" << endl;

  // /*** For part (c): Testing of queue: ***/
  // cout << endl << endl << "*** Queue: ***" << endl;
  // QueueFromList myQueue;
  //
  // cout << "Enqueueing to the queue: 1 2 3 4" << endl;
  //
  // myQueue.enqueue(1);
  // myQueue.enqueue(2);
  // myQueue.enqueue(3);
  // myQueue.enqueue(4);
  //
  // cout << "The head of the queue was " << myQueue.dequeue() << endl;
  // cout << "The head of the queue was " << myQueue.dequeue() << endl;
  //
  // cout << "Enqueueing to the queue: 5" << endl;
  //
  // myQueue.enqueue(5);
  //
  // cout << "The queue is ";
  // if (!myQueue.isEmpty())
  //     cout << "not ";
  // cout << "empty" << endl;
  //
  // cout << "The head of the queue was " << myQueue.dequeue() << endl;
  // cout << "The head of the queue was " << myQueue.dequeue() << endl;
  // cout << "The head of the queue was " << myQueue.dequeue() << endl;
  //
  // cout << "The queue is ";
  // if (!myQueue.isEmpty())
  //     cout << "not ";
  // cout << "empty" << endl;

  return 0;
}
