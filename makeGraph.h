#include "parseDat.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct Airport {
  // int airportID;
  long double latitude;
  long double longitude;
};

class makeGraph {
public:
  makeGraph();
  int getAirportIndex(int key);
  Airport getAirports(int key);

private:
  // void populateMap();
  void populateGraph();
  void addEdge();
  void initalizeVector();
  double distance(double lata, double latb, double longa, double longb);
  map<int, int> airport_index;
  vector<vector<double>> graph;
  vector<Airport> airports;
};