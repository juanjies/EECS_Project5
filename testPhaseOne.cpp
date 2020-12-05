#include "LinkedNodeClass.h"
#include "SortedListClass.h"

int main() {
  LinkedNodeClass< int > intLNC(NULL, 978, NULL);
  cout << intLNC.getValue() << endl;
  return 0;
}
