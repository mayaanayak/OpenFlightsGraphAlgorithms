#include "makeGraph.h"
#include "parseDat.h"
#include "iddfs.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main() {
  makeGraph mkg;
  mkg.populateGraph();

  mkg.getNeighbors(400);
  mkg.getNeighbors(600);
  


  return 0;
}