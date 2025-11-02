/*
Sample main file for testing the merkle tree implementation.
*/

#include "merkle_tree.h"

#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

void printHelp();
void testSuite();

int main(int argc, char **argv) {

  /* read from the file named in the first argument -- File should consist of
   * one value per line */
  // Make sure to error if the input arguments are wrong
  string input = "";
  if (argc != 2 || strcmp(argv[1], "") == 0) {
    printHelp();
  } else {
    input = argv[1];
  }

  /* Then stores input values in a data vector - intial tree is built over that
   * vector. */
  vector<int> data = readIntsFromFile(input);

  cout << "Inputted data: ";
  for (int i : data) {
    cout << i << " ";
  }
  cout << endl;

  /* Roots are printed as new values are inserted or overwritten. */
  merkleTree tree(data);

  cout << "Root value: ";
  tree.printRoot();

  tree.overwrite(7, 100);

  cout << "7 overwritten to 100" << endl;

  cout << "New root value: ";
  tree.printRoot();

  cout << "Inserting: 50" << endl;
  tree.insert(50);

  cout << "New root value: ";
  tree.printRoot();

  cout << "Inserting 1, 2, 3, 4, 5, 6" << endl;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(4);
  tree.insert(5);
  tree.insert(6);

  /* Tree is printed. */
  tree.printTree(tree.getRoot());

  /* Tree root is verified before and after a malicious attack occurs on the
  data vector. */
  cout << "Verifying tree..." << endl;
  cout << "Is data secure: ";
  tree.verify();
  cout << endl; // should be True

  cout << "Malicious data attack occurs!" << endl;
  tree.data[3] = 100;

  cout << "Verifying tree..." << endl;
  cout << "Is data secure: ";
  tree.verify();
  cout << endl; // should be False

  /* New tree is constructed from using just the insert function. */
  merkleTree newTree;
  cout << "Creating a new tree from inserts" << endl;
  cout << "Inserting: 20, 10, 1 to new tree" << endl;

  newTree.insert(20);
  newTree.insert(10);
  newTree.insert(1);

  /* Root is saved and verified. */
  cout << "New tree final root value: ";
  newTree.printRoot();

  cout << "Verifying tree..." << endl;
  cout << "Is data secure: ";
  newTree.verify();
  cout << endl; // should be True

  /* Tree is printed. */
  newTree.printTree(newTree.getRoot());

  // run custom tests
  testSuite();

  return 0;
}

void printHelp() {
  // print man
  fprintf(stderr, "merkle_tree: illegal option or missing argument\n"
                  "Usage: merkle_tree [input_file.txt]\n"
                  "\n"
                  "Options:\n"
                  "  -h, --help    Show this help message and exit\n");
  exit(1);
}

void testSuite() {
  cout << endl << "=== MerkleTree Test Suite ===" << endl;

  // 1. Basic construction
  {
    cout << "1. Basic construction... ";
    merkleTree mt({1, 2, 3, 4});
    assert(mt.getRoot() != nullptr);
    cout << "PASS" << endl;
  }

  // 2. Root consistency after rebuild
  {
    cout << "2. Root consistency after rebuild... ";
    vector<int> data{5, 6, 7, 8};
    merkleTree mt(data);
    string origRoot = mt.getRoot()->key;
    mt.rebuild();
    assert(mt.getRoot()->key == origRoot);
    cout << "PASS" << endl;
  }

  // 3. Verify unchanged data
  {
    cout << "3. Verify unchanged data... ";
    stringstream buf;
    streambuf *old = cout.rdbuf(buf.rdbuf());
    merkleTree mt({10, 20, 30});
    mt.verify();
    cout.rdbuf(old);
    assert(buf.str().find("True") != string::npos);
    cout << "PASS" << endl;
  }

  // 4. Detect tampered data
  {
    cout << "4. Detect tampered data... ";
    stringstream buf;
    streambuf *old = cout.rdbuf(buf.rdbuf());
    merkleTree mt({10, 20, 30});
    mt.data[1] = 999; // tamper
    mt.verify();
    cout.rdbuf(old);
    assert(buf.str().find("False") != string::npos);
    cout << "PASS" << endl;
  }

  // 5. Overwrite updates root
  {
    cout << "5. Overwrite updates root... ";
    merkleTree mt({1, 2, 3});
    string before = mt.getRoot()->key;
    mt.overwrite(2, 99);
    assert(mt.getRoot()->key != before);
    assert(mt.data[1] == 99);
    cout << "PASS" << endl;
  }

  // 6. Insert appends and rehashes
  {
    cout << "6. Insert appends and rehashes... ";
    merkleTree mt({1, 2});
    size_t n = mt.data.size();
    string before = mt.getRoot()->key;
    mt.insert(3);
    assert(mt.data.size() == n + 1);
    assert(mt.data.back() == 3);
    assert(mt.getRoot()->key != before);
    cout << "PASS" << endl;
  }

  // 7. Empty tree safety
  {
    cout << "7. Empty tree safety... ";
    merkleTree mt;
    assert(mt.getRoot() == nullptr);
    cout << "PASS" << endl;
  }

  cout << "=== All tests passed ===" << endl;
}
