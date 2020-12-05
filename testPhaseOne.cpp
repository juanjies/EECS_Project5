#include "LinkedNodeClass.h"
#include "SortedListClass.h"

int main() {
  LinkedNodeClass< int > intLNC(NULL, 978, NULL);
  cout << intLNC.getValue() << endl;
  LinkedNodeClass< float > decimalLNC(NULL, 3.14, NULL);
  cout << decimalLNC.getValue() << endl;
  return 0;
}
