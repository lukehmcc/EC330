// Name: Luke McCarthy
// Email: lukehmcc@bu.edu
// Collaborator Name: Ronald Chambergo
// Collaborator Email: ronc4908@bu.edu

#include "Problem4.h"
#include <iostream>
using namespace std;

bool isJumbled(char *str1, char *str2) {
  // create an 8 bit int array and count each letter
  int str1Array[256];
  int str2Array[256];
  // And clean up that
  for (int i = 0; i < 256; i++) {
    str1Array[i] = 0;
    str2Array[i] = 0;
  }
  for (int i = 0; str1[i] != '\0'; i++) {
    str1Array[(int)str1[i]]++;
  }
  for (int i = 0; str2[i] != '\0'; i++) {
    str2Array[(int)str2[i]]++;
  }
  // Then go through and check the arrays are the same
  for (int i = 0; i < 256; i++) {
    if (str1Array[i] != str2Array[i]) {
      cout << "not jumbled" << endl;
      return false;
    }
  }
  cout << "jumbled" << endl;
  return true;
}
