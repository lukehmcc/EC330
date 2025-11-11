#include "Problem3.h"
#include <iostream>

using namespace std;

int main() {
  cout << "The number of BU-IDs in the file is: " << threeA("TinyData.txt")
       << endl;
  cout << "The length of the shortest pangram in the file is: "
       << threeB("TinyData.txt") << endl;
  cout << "The number of valid dictionary words in the file is: "
       << threeC("TinyData.txt") << endl;
}
