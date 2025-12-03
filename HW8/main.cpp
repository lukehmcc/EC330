#include "Problem5.h"

int main(int argc, const char *argv[]) {

  if (argc != 3) {
    cout << "Please supply a file name & starting city as input" << endl;
    return -1;
  }

  Graph graph;
  graph.generateGraph(argv[1]);
  graph.distTwoNeighbors(argv[2]);

  return 0;
}
