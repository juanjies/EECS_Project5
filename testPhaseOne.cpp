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

  LinkedNodeClass < EventClass > LNCOne(NULL, eventOne, NULL);
  LinkedNodeClass < EventClass > LNCTwo(NULL, eventTwo,NULL);
  
  cout << "LinkedNodeClass testing" << endl;
  cout << LNCOne.getValue() << endl;
  cout << LNCTwo.getValue() << endl;

  SortedListClass < EventClass > SLCOne;
  SLCOne.insertValue(eventTwo);
  SLCOne.insertValue(eventOne);
  SLCOne.insertValue(eventThree);  

  cout << "SortedListClass testing" << endl;
  SLCOne.printForward();

  return 0;
}
