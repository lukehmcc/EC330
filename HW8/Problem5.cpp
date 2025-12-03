#include "Problem5.h"
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>
Graph::Graph() {}

void Graph::generateGraph(string fileName) {
  // open the file
  ifstream file(fileName);
  if (file.is_open()) {
    string line;
    // scan the first line
    getline(file, line);
    int nodeCount, edgeCount;
    std::istringstream in(line);
    if (!(in >> nodeCount >> edgeCount)) {
      std::cout << "Error: Incorrect Graph Format" << std::endl;
      return;
    }
    this->edgeCount = edgeCount;
    this->nodeCount = nodeCount;

    // set up to nothing
    adjMat.assign(nodeCount, vector<int>(nodeCount, -1));
    // and make diag 0
    for (int i = 0; i < nodeCount; ++i)
      adjMat[i][i] = 0;

    // now scan the rest of them and add them as edges (v)
    while (getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      // parse the city names
      if (line.front() != '"') {
        string city;
        int a, b;
        std::istringstream in(line);
        if (!(in >> city >> a >> b)) {
          std::cout << "Error: Incorrect Graph Format" << std::endl;
          return;
        }
        this->nodes.push_back(city);
        // set the reference value for each city so it's easy to find in the
        // matrix by the city name
        this->cityRef[city] = this->nodes.size() - 1;
        // now parse the edges
      } else if (line.front() == '"') {
        string garbo, city1, city2;
        int weight;
        std::istringstream in(line);
        if (!(in >> garbo >> city1 >> city2 >> weight)) {
          std::cout << "Error: Incorrect Graph Format" << std::endl;
          return;
        }
        adjMat[cityRef[city1]][cityRef[city2]] = weight;
        adjMat[cityRef[city2]][cityRef[city1]] = weight;
        // this shouldn't happen with a properly formatted file
      } else {
        std::cout << "Error: Incorrect Graph Format" << std::endl;
        return;
      }
    }

    // close the file
    file.close();
  }
}

void Graph::distTwoNeighbors(std::string startingCity) {
  // we have an adj matrix, so this is pretty simple
  // first create a list of all of it's adj (from matrix) and add these to the
  // set of locations
  set<std::string> neighbors;
  neighbors.merge(neighborGetter(cityRef[startingCity]));

  // then do another jump from all of those and add any new ones to the list
  set<std::string> neighbors2;
  for (std::string neighbor : neighbors) {
    neighbors2.merge(neighborGetter(cityRef[neighbor]));
  }
  neighbors.merge(neighbors2);
  neighbors.erase(startingCity);
  std::cout << startingCity << " distance 2 neighbors:" << std::endl;
  for (const std::string s : neighbors)
    std::cout << s << '\n';
}

// grabs all neighbor for specific ref
std::set<std::string> Graph::neighborGetter(int ref) {
  set<std::string> neighbors;
  for (int i = 0; i < nodeCount; ++i) {
    if (adjMat[ref][i] != -1 && i != ref) {
      neighbors.insert(nodes[i]);
    }
  }
  return neighbors;
}

void Graph::printMatrix(vector<vector<int>> mat) {
  for (int i = 0; i < nodeCount; i++) {
    for (int j = 0; j < nodeCount; j++) {
      std::cout << std::setw(3) << adjMat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
