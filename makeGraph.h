#pragma once

#include "parseDat.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct Airport {
  int airportID;
  long double latitude;
  long double longitude;
};

class makeGraph {
public:
  makeGraph();
  void populateGraph();
  int getAirportIndex(int key);
  Airport getAirports(int key);
  vector<vector<double>> getGraph();
  void addEdge(int sourceAirID, int destAirID);
  void deleteEdge(int sourceAirID, int destAirID);
  bool edgeExists(int sourceAirID, int destAirID);

private:
  double distance(double lata, double latb, double longa, double longb);
  map<int, int> airport_index;
  vector<vector<double>> graph;
  vector<Airport> airports;
};