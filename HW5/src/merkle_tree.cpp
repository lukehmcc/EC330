/*
Implementation of the merkle tree and node classes and helper function to read
from an inputed file.
*/

#include "merkle_tree.h"
#include <cstdint>

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
