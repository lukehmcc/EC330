/*
Implementation of the merkle tree and node classes and helper function to read
from an inputed file.
*/

// On how insert works: It is actually extremely simple. I add the data to the
// back of the array, then I rebuild the array with the rebuild tree function
// I had already built for other purposes. It's like 3 lines long.

#include "merkle_tree.h"
#include <cstdint>
#include <string>

using namespace std;

/* Hash function*/
inline string fnv1a(string const &text) {
  // 64 bit params
  uint64_t constexpr fnv_prime = 1099511628211ULL;
  uint64_t constexpr fnv_offset_basis = 14695981039346656037ULL;

  uint64_t hash = fnv_offset_basis;

  for (auto c : text) {
    hash ^= c;
    hash *= fnv_prime;
  }

  return to_string(hash);
}

Node::Node(const string &val) { key = val; }

/* Merkle Tree method for computing the hash of the concatenated hashes of
   children nodes Using the provided hash function, concatenates child hashes
   from left to right and returns the hash of the concatenation */
string merkleTree::concatenateHash(const vector<Node *> &nodes) {
  string merged;
  // concatenate hashes of all inputed nodes
  for (const Node *node : nodes) {
    merged += node->key;
  }

  // take hash of concatenated nodes
  string mergedHash = fnv1a(merged);

  return mergedHash;
}

/* Returns the root node of the Merkle tree */
Node *merkleTree::getRoot() { return this->root; }

/* Helper function to read integers from a file */
vector<int> readIntsFromFile(const string &filename) {
  vector<int> data;
  string stringLines;
  ifstream fileLines(filename);
  while (getline(fileLines, stringLines)) {
    data.push_back(stoi(stringLines));
  }
  return data;
}

// constructor with argument of data
merkleTree::merkleTree(const vector<int> &data) {
  this->data = data;
  root = rebuild();
}

// constructor
merkleTree::merkleTree() { root = nullptr; }

// insert a new value
void merkleTree::insert(int newValue) {
  // add data, rebuild, and set new root
  data.push_back(newValue);
  root = rebuild();
}

// Recursively move to the next level and reduce the size
vector<Node *> merkleTree::recursiveReduce(vector<Node *> &nodes) {
  if (nodes.size() == 1) {
    // set the root to that
    return nodes;
  }
  // pad out to multiple of 4
  while (nodes.size() % 4 != 0) {
    nodes.push_back(new Node("NULL"));
  }

  vector<Node *> reducedNodes;
  // process all the old ones
  for (int i = 0; i < nodes.size(); i += 4) {
    // concat them and make new thing
    vector<Node *> subVec;
    for (int j = 0; j < 4; j++) {
      // Don't actually push null to the concat
      if (nodes[j + i]->key != "NULL") {
        subVec.push_back(nodes[i + j]);
      }
    }

    Node *newNode = new Node(fnv1a(concatenateHash(subVec)));
    newNode->children = subVec;
    reducedNodes.push_back(newNode);
  }
  return recursiveReduce(reducedNodes);
}

// from stored data, rebuild the merkel tree
Node *merkleTree::rebuild() {
  // lets build this from the ground up
  // build the leaves
  vector<Node *> nodes;
  for (int i = 0; i < data.size(); i++) {
    // make the new node and populate it
    // Hash the data at that block and generate a new Node
    nodes.push_back(new Node(fnv1a(to_string(data[i]))));
  }

  // recursively reduce that set of leaves by multiple of 4 until 1 remains
  // that single node is now the root, return that
  return recursiveReduce(nodes).front();
}

// print root of tree
void merkleTree::printRoot() {
  // send that to cout
  cout << root->key << endl;
}

// override given value with newly inputed value
void merkleTree::overwrite(int originalValue, int newValue) {
  // first check if the object is in the array
  int index = -1;
  for (int i = 0; i < data.size(); i++) {
    if (data[i] == originalValue) {
      index = i;
      break;
    }
  }
  // if isn't, return
  if (index == -1) {
    return;
  }
  // if it is, overwrite & rehash
  data[index] = newValue;
  root = rebuild();
}

// visualization of tree
void merkleTree::printTree(const Node *node, int depth) {
  // first print the root
  cout << "Level " << depth << ": " << node->key << endl;
  // and assemble to toPrint vec
  vector<Node *> toPrint = node->children;
  string offset = "";

  // keep printing & building
  while (toPrint.size() != 0) {
    depth++; // now at next depth
    offset += " ";
    vector<Node *> nextToPrint; // store upcoming level
    for (int i = 0; i < toPrint.size(); i++) {
      if (toPrint[i]->key != "NULL") {
        cout << offset << "Level " << depth << ": " << toPrint[i]->key << endl;
      }
      for (int j = 0; j < toPrint[i]->children.size(); j++) {
        nextToPrint.push_back(toPrint[i]->children[j]);
      }
    }
    toPrint = nextToPrint;
  }
}

// store the current root, then given current data vector,
// rebuild tree and compare the original root to the rebuilt
// root. print "True" if they match, "False" if else
void merkleTree::verify() {
  Node *newBuild = rebuild();
  if (newBuild->key == root->key) {
    cout << "True";
  } else {
    cout << "False";
  }
}
