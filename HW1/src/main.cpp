#include "Problem4.h"
#include <iostream>

int main() {
  char str1[] = "abcd";
  char str2[] = "cbad";
  const bool isJum = isJumbled(str1, str2);
  std::cout << "String 1: " << str1 << ", String 2: " << str2
            << ", is isJumbled: " << (isJum ? "true" : "false") << std::endl;
  return 0;
}
