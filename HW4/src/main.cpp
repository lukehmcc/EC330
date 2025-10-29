//
//  main.cpp
//  Linked_List_zeroSort
//
//  Created by Luke McCarthy
//

#include "LinkedList.h"
#include <vector>

bool equal(const LinkedList &L, const string &expect) {
  string s;
  for (Node *p = L.head; p; p = p->next) {
    s += to_string(p->data);
    if (p->next)
      s += ' ';
  }
  return s == expect;
}

LinkedList *getLL() {
  LinkedList *myLL = new LinkedList();

  myLL->insertToTail(1);
  myLL->insertToTail(4);
  myLL->insertToTail(0);
  myLL->insertToTail(8);
  myLL->insertToTail(-6);
  myLL->insertToTail(0);
  return myLL;
}

int main(int argc, const char *argv[]) {

  LinkedList *myLL = getLL();

  cout << "Linked list data: ";
  myLL->print();

  myLL->zeroSort();
  cout << "Sorted Linked list data: ";
  myLL->print();

  struct TC {
    string name;
    int v1, v2;
    string want;
  };

  // input: 1 4 0 8 -6 0
  vector<TC> tests = {
      {"swap interior 4↔8", 4, 8, "1 8 0 4 -6 0"},
      {"swap 1↔4", 1, 4, "4 1 0 8 -6 0"},
      {"swap self -6↔-6", -6, -6, "1 4 0 8 -6 0"},
      {"swap 0↔8", 0, 8, "1 4 8 0 -6 0"},
      {"swap -6-0 -6↔0", -6, 0, "1 4 -6 8 0 0"},
      {"swap non-existent 99↔0", 99, 0, "1 4 0 8 -6 0"},
      {"swap nullptrs", 0, 0, "1 4 0 8 -6 0"}, // both findFirst calls return
                                               // the same first-0 node -> no-op
      {"swap 8↔1", 8, 1, "8 4 0 1 -6 0"},
      {"swap 4↔4", 4, 4, "1 4 0 8 -6 0"},
      {"swap 0↔-6", 0, -6, "1 4 -6 8 0 0"},
      {"swap 1↔0", 1, 0, "0 4 1 8 -6 0"},
      {"swap last two 8↔1", 8, 1, "8 4 0 1 -6 0"}};
  delete myLL;
  myLL = getLL();
  cout << "input: ";
  myLL->print();
  int pass = 0, fail = 0;
  for (auto &t : tests) {
    // refresh linked list each time
    delete myLL;
    myLL = getLL();
    Node *n1 = myLL->findFirst(t.v1);
    Node *n2 = myLL->findFirst(t.v2);
    myLL->swap(n1, n2);
    bool ok = equal(*myLL, t.want);
    if (!ok) {
      cout << "❌ FAIL | " << t.name << '\n';
      cout << "  expected: " << t.want << '\n';
      cout << "  got:      ";
      myLL->print();
    } else {
      cout << "✅ PASS | " << t.name << '\n';
      cout << "  expected: " << t.want << '\n';
      cout << "  got:      ";
      myLL->print();
    }
    ok ? ++pass : ++fail;
  }
  cout << "\nSummary: " << pass << " passed, " << fail << " failed\n";
  delete myLL;
  return 0;
}
