#include "Problem5.h"
#include <fstream>
#include <sstream>
Graph::Graph() {}

void Graph::generateGraph(string fileName) {
  // open the file
  ifstream file(fileName);
  if (file.is_open()) {
    string line;
    // scan the first line
    getline(file, line);
    int vertexCount, edgeCount;
    std::istringstream in(line);
    if (!(in >> vertexCount >> edgeCount)) {
      std::cout << "Error: Incorrect Graph Format" << std::endl;
      return;
    }
    this->edgeCount = edgeCount;
    this->nodeCount = vertexCount;

    // now scan the rest of them and add them as edges (v)
    while (getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      // parse the edges
      if (line.front() == '"') {
        string garbo, apt1, apt2;
        int weight;
        std::istringstream in(line);
        if (!(in >> garbo >> apt1 >> apt2 >> weight)) {
          std::cout << "Error: Incorrect Graph Format" << std::endl;
          return;
        }
        // parse each city name
      } else {
        string city;
        int a, b;
        std::istringstream in(line);
        if (!(in >> city >> a >> b)) {
          std::cout << "Error: Incorrect Graph Format" << std::endl;
          return;
        }
        this->nodes.push_back(city);
      }
    }

    // close the file
    file.close();
  }
}
