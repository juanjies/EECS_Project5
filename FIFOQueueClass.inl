#include <iostream>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"

using namespace std;
// Programmer: Juan-Jie Sun
// Date: December 2020
// Purpose: to implement a templated
//          "first-in-first-out" queue data structure

template < class T >
FIFOQueueClass< T >::FIFOQueueClass() {
  head = NULL;
  tail = NULL;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass() {
  this -> clear();
}

template < class T >
void FIFOQueueClass< T >::enqueue(const T &newItem) {
  LinkedNodeClass< T >* insertedNode = NULL;

  if (head == NULL) {
    tail = new LinkedNodeClass< T >(NULL, newItem, NULL);
    head = tail;
  }
  else {
    insertedNode = new LinkedNodeClass< T >(tail, newItem, NULL);
    tail = insertedNode;
    tail -> setBeforeAndAfterPointers();
    insertedNode = NULL;
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem) {
  LinkedNodeClass< T >* temp = head;

  if (temp == NULL) {
    return (false);
  }
  else {
    outItem = head -> getValue();
    head = head -> getNext();
    delete temp;
    temp = head;
    if (temp != NULL) {
      temp -> setPreviousPointerToNull();
    }
    else if (temp == NULL) {
      tail = temp;
    }
    return (true);
  }
}

template < class T >
void FIFOQueueClass< T >::print() const {
  LinkedNodeClass< T >* temp = head;

  while (temp != NULL) {
    cout << temp -> getValue() << " ";
    temp = temp -> getNext();
  }
  cout << endl;
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const {
  LinkedNodeClass< T >* temp = head;
  int numCount = 0;

  while (temp != NULL) {
    temp = temp -> getNext();
    numCount++;
  }
  return (numCount);
}

template < class T >
void FIFOQueueClass< T >::clear() {
  LinkedNodeClass< T >* temp = head;
  while (temp != NULL) {
    head = head -> getNext();
    delete temp;
    temp = head;
  }
  tail = NULL;
}

