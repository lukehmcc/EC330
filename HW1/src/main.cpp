#include "Problem4.h"
#include "Problem5.h"
#include <cstring>
#include <iostream>
using namespace std;

// stubs
void problem4tests();
void problem5tests();
void runProblem4Test(const char *s1, const char *s2, bool expected);
void runProblem5Test(const char *input, const char *expected);

// int main() {
//   problem4tests();
//   problem5tests();
//   return 0;
// }

/* All test cases for isJumbled() */
void problem4tests() {
  // 1. Simple anagram – same characters, different order
  runProblem4Test("abcd", "cbad", true); // basic case【1】

  // 2. Same length, one mismatched character
  runProblem4Test("abcd", "abce", false); // should fail

  // 3. Different lengths – early reject
  runProblem4Test("abc", "abcd", false); // length check【2】

  // 4. Two empty strings – trivially jumbled
  runProblem4Test("", "", true); // empty case

  // 5. Repeated characters, same multiset
  runProblem4Test("aabbcc", "abcabc", true); // repeats handled

  // 6. Same characters, different grouping
  runProblem4Test("aabbcc", "abccba", true); // another repeat test

  // 7. Case‑sensitivity (ASCII values differ)
  runProblem4Test("Hello", "hello", false); // case matters

  // 8. Spaces are treated as characters
  runProblem4Test("a b c", "c b a", true); // whitespace included【3】

  // 9. Digits and punctuation mixed
  runProblem4Test("123!@#", "#!@321", true); // non‑alpha chars

  // 10. Extra whitespace changes the multiset
  runProblem4Test("abcd", "ab cd", false); // length/char mismatch
}

/* Helper to print a single test result */
void runProblem4Test(const char *s1, const char *s2, bool expected) {
  bool result = isJumbled(const_cast<char *>(s1), const_cast<char *>(s2));
  cout << "String 1: \"" << s1 << "\", String 2: \"" << s2 << "\""
       << " → expected: " << (expected ? "true" : "false")
       << ", actual: " << (result ? "true" : "false")
       << (result == expected ? "  ✅" : "  ❌") << endl;
}

void problem5tests() {
  // 1. Even length
  runProblem5Test("dragon", "rdgano");

  // 2. Odd length
  runProblem5Test("apple", "palpe");

  // 3. Single char
  runProblem5Test("a", "a");

  // 4. Empty string
  runProblem5Test("", "");

  // 5. Palindrome even
  runProblem5Test("noon", "onno");

  // 6. Palindrome odd
  runProblem5Test("racecar", "arecacr");

  // 7. Mixed case
  runProblem5Test("AbC", "bAC");

  // 8. With spaces
  runProblem5Test("a b", " ab");

  // 9. With digits
  runProblem5Test("12345", "21435");

  // 10. Long string
  runProblem5Test("supercalifragilisticexpialidocious",
                  "usepcrlafiarigiltscixeipladicooisu");
}

/* Helper to print a single test result */
void runProblem5Test(const char *input, const char *expected) {
  char out[256] = {0};
  strXpos(out, input);
  cout << "Input: \"" << input << "\" → expected: \"" << expected
       << "\", actual: \"" << out << "\""
       << (strcmp(out, expected) == 0 ? "  ✅" : "  ❌") << endl;
}
