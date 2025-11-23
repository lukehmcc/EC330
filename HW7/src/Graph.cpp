#include "Graph.h"
#include <climits>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
Graph::Graph() {}

// generates the graph based on text input
void Graph::generateGraph(string fileName) {
  // open the file
  ifstream file(fileName);
  if (file.is_open()) {
    string line;
    // scan the first line
    getline(file, line);
    int vertexCount, edgeCount;
    string graphType;
    std::istringstream in(line);
    in >> vertexCount >> edgeCount >> std::ws;
    getline(in, graphType);
    this->graphType = graphType;
    this->edgeCount = edgeCount;
    this->vertexCount = vertexCount;

    // populate the vertexes & adj list
    for (int i = 0; i < vertexCount; i++) {
      vertices.insert(i);
      adjList.push_back({});
    }

    // now scan the rest of them and add them as edges (v)
    while (getline(file, line)) {
      int node1, node2, weight;
      std::istringstream in(line);
      in >> node1 >> node2 >> weight;
      addEdge(directedEdge(node1, node2), weight);
    }

    // close the file
    file.close();
  }
}

// prints human readable graph
void Graph::printGraph() {
  for (int i = 0; i < adjList.size(); i++) {
    std::cout << i << ": ";
    set<int> cur = adjList.at(i);
    for (const int elem : cur) {
      int weight = weights[make_pair(i, elem)];
      std::cout << elem << " (" << weight << ") ";
    }
    std::cout << endl;
  }
  std::cout << endl;
}

// finds the lowest reachable for each input
// It does this with a BFS search that progressively works it's way through each
// layer of neighbors.
//
// Runtime: O(V + E). It has to do an operation on each verticie & each edge.
// But it doesn't grow exponentially, just linearly with size & density of
// graph.
void Graph::lowestReachable() {
  for (int i = 0; i < vertices.size(); i++) {
    int lowest = findLowest(i);
    std::cout << "The lowest reachable vertex for " << i;
    if (lowest != -1) {
      std::cout << " is " << lowest << std::endl;
    } else {
      std::cout << " doesn't exist" << std::endl;
    }
  }
}

// finds the lowest reachable index
int Graph::findLowest(int start) {
  // algo BFS
  std::queue<int> q;
  std::vector visited(vertices.size(), 0);
  int lowest = INT_MAX;
  q.push(start);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    if (cur != start && cur < lowest) {
      lowest = cur;
    }
    if (visited[cur]) {
      continue;
    } else {
      visited[cur] = 1;
    }
    set<int> adjs = adjList.at(cur);
    for (int adj : adjs) {
      if (!visited[adj]) {
        q.push(adj);
      }
    }
  }

  return (lowest == INT_MAX) ? -1 : lowest;
}

// checks if edge already exists
bool Graph::isEdge(directedEdge newEdge) {
  // count is 1 if it exists, 0 if not
  return edges.count(newEdge);
}

// adds a new edge w/ weight
void Graph::addEdge(directedEdge newEdge, int weight) {
  edges.insert(newEdge);
  weights.insert({newEdge, weight});
  adjList[newEdge.first].insert(newEdge.second);
}

// adds next vertex (not very useful)
int Graph::addVertex() {
  int nextIndex = vertices.size();
  vertices.insert(nextIndex);
  adjList.push_back({});
  return nextIndex;
}
