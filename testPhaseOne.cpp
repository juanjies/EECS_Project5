#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "EventClass.h"

int main() {
  EventClass eventOne(1, 1);
  EventClass eventTwo(2, 2);

  LinkedNodeClass< EventClass > intLNCOne(NULL, eventOne, NULL);
  LinkedNodeClass< EventClass > intLNCTwo(NULL, eventTwo,NULL);
  if (intLNCOne < intLNCTwo)  {
    cout << "eventOne happens before eventTwo" << endl;
  }

  SortedListClass< int > intSLC;
  intSLC.insertValue(5);
  intSLC.insertValue(9);
  intSLC.insertValue(7);
  intSLC.insertValue(8);
  intSLC.printForward();
  return 0;
}
