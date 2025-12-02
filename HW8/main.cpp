#include "Problem5.h"

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    cout << "Please supply a file name as input" << endl;
    return -1;
  }

  Graph graph;
  graph.generateGraph(argv[1]);

  return 0;
}
