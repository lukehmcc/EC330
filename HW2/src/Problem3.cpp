// Problem3.cpp
// Author: Luke McCarthy
#include "Problem3.h"
using namespace std;

vector<int> checkBalanced(vector<string> dataset) {
  vector<int> toReturn(dataset.size());
  for (int i = 0; i < dataset.size(); i++) {
    int orderAcc = 0;
    int outOfOrder = 0;
    for (int j = 0; j < dataset.at(i).size(); j++) {
      if (dataset.at(i).at(j) == '(') {
        orderAcc++;
      } else if (dataset.at(i).at(j) == ')') {
        if (orderAcc <= 0) {
          outOfOrder++;
        } else {
          orderAcc--;
        }
      }
    }
    if ((orderAcc == 0 && outOfOrder == 0) ||
        (orderAcc == 1 && outOfOrder == 1)) {
      toReturn.at(i) = 1;
    } else {
      toReturn.at(i) = 0;
    }
  }
  return toReturn;
}
