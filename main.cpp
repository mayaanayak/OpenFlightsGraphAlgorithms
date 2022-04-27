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
  vector<int> ans = mkg.getNeighbors(5000);
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << endl;
  }
  


  return 0;
}