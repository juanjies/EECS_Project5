#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"

int main() {
  EventClass eventOne(1, EVENT_ARRIVE_EAST);
  EventClass eventTwo(2, EVENT_ARRIVE_WEST);

  LinkedNodeClass< EventClass > intLNCOne(NULL, eventOne, NULL);
  LinkedNodeClass< EventClass > intLNCTwo(NULL, eventTwo,NULL);
  
  // cout << intLNCOne.getValue() << endl;
  cout << eventOne;

  SortedListClass< int > intSLC;
  intSLC.insertValue(5);
  intSLC.insertValue(9);
  intSLC.insertValue(7);
  intSLC.insertValue(8);
  intSLC.printForward();
  return 0;
}
