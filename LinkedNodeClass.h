#ifndef _LinkedNodeClass_H_
#define _LinkedNodeClass_H_

// Programmer: Juan-Jie Sun
// Date: November 2020
// Purpose: This class will be used to store individual nodes of 
//          a doubly-linked data structure. The content of a node is 
//          set as templated so the content can be any data type 

template < class T >
class LinkedNodeClass {
  private:
    LinkedNodeClass< T >* prevNode; 
    // Will point to the node that comes before
    // this node in the data structure. Will be
    // NULL if this is the first node.
    T nodeVal; 
    // The value contained within this node.
    LinkedNodeClass< T >* nextNode; 
    // Will point to the node that comes after
    // this node in the data structure. Will be
    // NULL if this is the last node.

  public:
    // The ONLY constructor for the linked node class - it takes in the
    // newly created node's previous pointer, value, and next pointer,
    // and assigns them.
    LinkedNodeClass(
      LinkedNodeClass< T >* inPrev, //Address of node that comes before this one
      const T &inVal, // Value to be contained in this node
      LinkedNodeClass< T >* inNext //Address of node that comes after this one
    );
    //Returns the value stored within this node.
    T getValue() const;
    //Returns the address of the node that follows this node.
    LinkedNodeClass< T >* getNext() const;
    //Returns the address of the node that comes before this node.
    LinkedNodeClass< T >* getPrev() const;
    //Sets the object’s next node pointer to NULL.
    void setNextPointerToNull();
    //Sets the object's previous node pointer to NULL.
    void setPreviousPointerToNull();
    //This function DOES NOT modify "this" node. Instead, it uses
    //the pointers contained within this node to change the previous
    //and next nodes so that they point to this node appropriately.
    //In other words, if "this" node is set up such that its prevNode
    //pointer points to a node (call it "A"), and "this" node's
    //nextNode pointer points to a node (call it "B"), then calling
    //setBeforeAndAfterPointers results in the node we're calling
    //"A" to be updated so its "nextNode" points to "this" node, and
    //the node we're calling "B" is updated so its "prevNode" points
    //to "this" node, but "this" node itself remains unchanged.
    void setBeforeAndAfterPointers();
    //overload the operators that I will use for LinkedNodeClass
    //in implementing SortedListClass
    bool operator>=(const LinkedNodeClass< T > &rhs)  {
      return (nodeVal >= rhs.getValue());
    }
    bool operator<(const LinkedNodeClass< T > &rhs)  {
      return (nodeVal < rhs.getValue());
    }
};

#include "LinkedNodeClass.inl"
#endif