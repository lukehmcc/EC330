#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/* Implements a directed, weighted graph, where vertices can have color */
class Graph {

public:
  Graph();
  void generateGraph(string fileName);

private:
  int nodeCount;
  int edgeCount;
  vector<string> nodes;
  vector<vector<int>> adjMat;
};

#endif /* Graph_h */
