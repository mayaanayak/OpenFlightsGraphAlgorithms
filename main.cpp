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
  int index = mkg.getAirportIndex(7458);
  cout << index << endl;
  cout << mkg.getAirportID(index) << endl;
  


  return 0;
}