#include <iostream>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"

using namespace std;
// Programmer: Juan-Jie Sun
// Date: November 2020
// Purpose: to implement the "first-in-first-out" queue data structure

FIFOQueueClass::FIFOQueueClass() {
  head = NULL;
  tail = NULL;
}

FIFOQueueClass::~FIFOQueueClass() {
  this -> clear();
}

void FIFOQueueClass::enqueue(const int &newItem) {
  LinkedNodeClass* insertedNode = NULL;

  if (head == NULL) {
    tail = new LinkedNodeClass(NULL, newItem, NULL);
    head = tail;
  }
  else {
    insertedNode = new LinkedNodeClass(tail, newItem, NULL);
    tail = insertedNode;
    tail -> setBeforeAndAfterPointers();
    insertedNode = NULL;
  }
}
//RESUBMISSION CODE UPDATE
bool FIFOQueueClass::dequeue(int &outItem) {
  LinkedNodeClass* temp = head;

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

void FIFOQueueClass::print() const {
  LinkedNodeClass* temp = head;

  while (temp != NULL) {
    cout << temp -> getValue() << " ";
    temp = temp -> getNext();
  }
  cout << endl;
}

int FIFOQueueClass::getNumElems() const {
  LinkedNodeClass* temp = head;
  int numCount = 0;

  while (temp != NULL) {
    temp = temp -> getNext();
    numCount++;
  }
  return (numCount);
}

void FIFOQueueClass::clear() {
  LinkedNodeClass* temp = head;
  while (temp != NULL) {
    head = head -> getNext();
    delete temp;
    temp = head;
  }
  tail = NULL;
}

