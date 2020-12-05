#include <cstdlib>
#include <iostream>
#include "constants.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"

using namespace std;
// Programmer: Juan-Jie Sun
// Date: November 2020
// Purpose: The sorted list class does not store any data directly. 
//          Instead, it contains a collection of LinkedNodeClass objects
//          each of which contains one element.

template < class T >
SortedListClass< T >::SortedListClass() {
  head = NULL;
  tail = NULL;
}

template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs) {  
  // copy ctor for deep copy
  LinkedNodeClass< T >* tempOne = rhs.head;
  LinkedNodeClass< T >* tempTwoPrev = head;
  LinkedNodeClass< T >* tempTwoNext = NULL;

  // if the list is empty
  if (rhs.head == NULL && rhs.tail == NULL) {
    head = NULL;
    tail = NULL;
  }
  // if the list is NOT empty
  else if (rhs.head != NULL && rhs.tail != NULL) {
    for (int i = 0; i < rhs.getNumElems(); i++) {
      // copy the first node and link the head to it
      if (i == 0) {
        tempTwoNext = new LinkedNodeClass< T >(NULL, 
                                          tempOne -> getValue(), NULL);
        tempTwoPrev = tempTwoNext;
        head = tempTwoPrev;
        tempOne = tempOne -> getNext();
      }
      // copy the last node
      else if (i == (rhs.getNumElems() - 1)) {
        tempTwoNext = new LinkedNodeClass< T >(tempTwoPrev,
                                          tempOne -> getValue(), NULL);
        tempTwoPrev = tempTwoNext;
        tempTwoPrev -> setBeforeAndAfterPointers();
        tail = tempTwoNext;
      }
      // copy other nodes in the middle
      else {
        tempTwoNext = new LinkedNodeClass(tempTwoPrev,
                                          tempOne -> getValue(), NULL);
        tempTwoPrev = tempTwoNext;
        tempTwoPrev -> setBeforeAndAfterPointers();
        tempOne = tempOne -> getNext();
      }
    } 
  }
}

template < class T >
SortedListClass< T >::~SortedListClass() {
  this -> clear();
}

template < class T >
void SortedListClass< T >::clear() {
  LinkedNodeClass< T >* temp = head;
  if (head == NULL && tail == NULL) {
    ;
  }
  else {
    while (temp != NULL) {
      temp = temp -> getNext();
      delete head;
      head = temp;
    }
    tail = NULL;
  }
}

template < class T >
void SortedListClass< T >::insertValue(const T &valToInsert) {
  LinkedNodeClass< T >* temp = head;
  LinkedNodeClass< T >* insertedNode = NULL;

  int tempVal = 0;
  // if the list is empty
  if (temp == NULL) {
    insertedNode = new LinkedNodeClass(NULL, valToInsert, NULL);
    head = insertedNode;
    tail = insertedNode;
    temp = head;
    insertedNode = NULL;
  }
  // the list is NOT empty
  else if (temp != NULL) {
    tempVal = temp -> getValue();
    // find the correct location to insert
    while (valToInsert >= tempVal && temp != tail) {
        temp = temp -> getNext(); 
        tempVal = temp -> getValue();
    }
    // if valToInsert is greater than all on the list
    if (valToInsert >= tempVal && temp == tail) {
      insertedNode = new LinkedNodeClass(temp, valToInsert, NULL);
      insertedNode -> setBeforeAndAfterPointers();
      tail = insertedNode;
      insertedNode = NULL;
    }
    // if valToInsert is less than all on the list
    else if (valToInsert < tempVal && temp == head) {
      insertedNode = new LinkedNodeClass(NULL, valToInsert, temp);
      insertedNode -> setBeforeAndAfterPointers();
      head = insertedNode;
      insertedNode = NULL;
    }
    // any others in the middle of the list
    else {
      insertedNode = new LinkedNodeClass(temp -> getPrev(),
                                         valToInsert,
                                         temp);
      insertedNode -> setBeforeAndAfterPointers();
      insertedNode = NULL;
    }
  }
}

template < class T >
void SortedListClass< T >::printForward() const {
  LinkedNodeClass< T >* temp = head;
  cout << "Forward List Contents Follow:" << endl;
  
  while (temp != NULL) {
    cout << "  " << temp -> getValue() << endl;
    temp = temp -> getNext();
  }
  cout << "End of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const {
  LinkedNodeClass< T >* temp = tail;
  cout << "Backward List Contents Follow:" << endl;

  while (temp != NULL) {
    cout << "  " << temp -> getValue() << endl;
    temp = temp -> getPrev();
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(int &theVal) {
  LinkedNodeClass< T >* temp = head;

  if (temp == NULL) {
    return (false);
  }
  else {
    theVal = head -> getValue();
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
bool SortedListClass< T >::removeLast(int &theVal) {
  LinkedNodeClass< T >* temp = tail;

  if (temp == NULL) {
    return (false);
  }
  else {
    theVal = tail -> getValue();
    tail = tail -> getPrev();
    delete temp;
    temp = tail;
    if (temp != NULL) {
      temp -> setNextPointerToNull();
    }
    else if (temp == NULL) {
      head = temp;
    }
    return (true);
  }
} 

template < class T >
int SortedListClass< T >::getNumElems() const {
  LinkedNodeClass< T >* temp = head;
  int numElems = 0;
  
  while (temp != NULL) {
    numElems++;
    temp = temp -> getNext();
  }
  return (numElems);
}

template < class T >
bool SortedListClass< T >::getElemAtIndex(const int index, 
                                            T &outVal) const {
  LinkedNodeClass< T >* temp = head;
  // within the list range
  if (index < (this -> getNumElems())) {
    for (int i = 0; i < index; i++) {
      temp = temp -> getNext();
    }
    outVal = temp -> getValue();
    return (true);
  }
  // out of the list range
  else {
    return (false);
  }
}


