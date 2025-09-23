#include "Problem3.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<pair<vector<string>, vector<int>>> tests = {
      {{"()"}, {1}},         {{")("}, {1}},          {{"(()"}, {0}},
      {{"())"}, {0}},        {{"(((("}, {0}},        {{"))))"}, {0}},
      {{"()()"}, {1}},       {{")(()"}, {1}},        {{"(()))("}, {1}},
      {{"(()())"}, {1}},     {{"))(("}, {0}},        {{"(())()"}, {1}},
      {{")(()(()))("}, {1}}, {{"))(()(()))(("}, {0}}};
  for (auto &[inp, exp] : tests) {
    vector<int> got = checkBalanced(inp);
    bool ok = (got == exp);
    cout << "Test: ";
    for (auto &s : inp)
      cout << '"' << s << "\" ";
    cout << "\nExpected: ";
    for (int v : exp)
      cout << v << ' ';
    cout << "\nGot:      ";
    for (int v : got)
      cout << v << ' ';
    cout << "\n" << (ok ? "✅ PASS" : "❌ FAIL") << "\n\n";
  }
  return 0;
}
