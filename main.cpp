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
  bool check = mkg.edgeExists(3043, 3131);
  cout << check << endl;

  return 0;
}