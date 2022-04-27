#include "makeGraph.h"
#include "parseDat.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main() {
  makeGraph mkg;
  // check if data works
  mkg.populateGraph();
  vector<vector<double>> graph = mkg.getGraph();
  vector<int> ans = mkg.getNeighbors(0);
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << endl;
  }
  cout << "add Edge" << endl;
  mkg.addEdge(1, 10);
  ans = mkg.getNeighbors(0);
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << endl;
  }
  cout << "delete Edge" << endl;
  mkg.deleteEdge(1, 10);
  ans = mkg.getNeighbors(0);
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << endl;
  }
  


  return 0;
}