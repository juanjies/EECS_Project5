#include "LinkedNodeClass.h"
#include "SortedListClass.h"

int main() {
  LinkedNodeClass< int > intLNC(NULL, 978, NULL);
  cout << intLNC.getValue() << endl;
  LinkedNodeClass< float > decimalLNC(NULL, 3.14, NULL);
  cout << decimalLNC.getValue() << endl;

  SortedListClass< int > intSLC;
  intSLC.insertValue(5);
  intSLC.insertValue(9);
  intSLC.insertValue(7);
  intSLC.insertValue(8);
  intSLC.printForward();
  return 0;
}
