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
  // prints out all locations that can be reached with two jumps
  void distTwoNeighbors(std::string startingCity);

private:
  int nodeCount;
  int edgeCount;
  vector<string> nodes;
  // set the reference value for each city so it's easy to find in the
  // matrix by the city name
  unordered_map<string, int> cityRef;
  vector<vector<int>> adjMat;
  void printMatrix(vector<vector<int>> mat);
  std::set<std::string> neighborGetter(int ref);
};

#endif /* Graph_h */
