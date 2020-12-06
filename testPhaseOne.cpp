#include <iostream>
using namespace std;

#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"

int main() {
  EventClass eventOne(1, EVENT_ARRIVE_EAST);
  EventClass eventTwo(2, EVENT_ARRIVE_WEST);
  EventClass eventThree(3, EVENT_ARRIVE_NORTH);  

  SortedListClass < EventClass > SLCOne;
  SLCOne.insertValue(eventTwo);
  SLCOne.insertValue(eventOne);
  SLCOne.insertValue(eventThree);  
  cout << endl;
  
  cout << "SortedListClass testing" << endl;
  cout << endl;
  SLCOne.printForward();
  cout << endl;

  FIFOQueueClass < EventClass > queueOne;  
  queueOne.enqueue(eventTwo);
  queueOne.enqueue(eventOne);
  queueOne.enqueue(eventThree);  

  cout << "FIFOQueueClass testing" << endl;
  cout << endl;
  queueOne.print();

  return 0;
}
