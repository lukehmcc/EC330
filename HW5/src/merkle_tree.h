/*
Header file for merkle tree implementation
*/

#ifndef MerkleTree_h
#define MerkleTree_h

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  string key;              // store hash
  vector<Node *> children; // store vector of children nodes
  Node(const string &val); // constructor
};

class merkleTree {
private:
  Node *root; // pointer to root node
public:
  vector<int> data;                    // store data that tree is built on
  merkleTree();                        // constructor
  string fnv1a(string const &text);    // expose the hash funct
  merkleTree(const vector<int> &data); // constructor with arguments
  string concatenateHash(const vector<Node *> &nodes); // merge and rehash nodes
  void printTree(const Node *node, int depth = 0);     // visualization of tree
  void verify(); // store the current root, then given current data vector,
                 // rebuild tree and compare the original root to the rebuilt
                 // root. print "True" if they match, "False" if else
  void overwrite(int originalValue,
                 int newValue); // override given value with newly inputed value
                                // and rehash tree
  void insert(int newValue); // insert new value to the end of data vector and
                             // rehash tree
  void printRoot();          // print root of tree
  Node *getRoot();           // returns root node
  Node *rebuild();           // rebuilds the merkel tree
  vector<Node *>
  // recursively moves up the tree and returns the root
  recursiveReduce(vector<Node *> &nodes);
};

vector<int> readIntsFromFile(
    const string &filename); // helper function to read from inputed file

#endif /* MerkleTree_h*/
