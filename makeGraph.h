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
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Airport {
  int airportID;
  long double latitude;
  long double longitude;
};

class makeGraph {
public:
  makeGraph();
  makeGraph(map<int, int> a, map<int, vector<int>> n, vector<vector<double>> g);
  int getAirportIndex(int key);
  Airport getAirports(int key);
  vector<vector<double>> getGraph();
  void addEdge(int sourceAirID, int destAirID);
  void deleteEdge(int sourceAirID, int destAirID);
  bool edgeExists(int sourceAirID, int destAirID);
  double routeDistance(int sourceAirID, int destAirID);
  void populateGraph();
  vector<int> getNeighbors(int index);
  int getAirportID(int index);

private:
  double distance(double lata, double latb, double longa, double longb);
  map<int, int> airport_index;
  map<int, vector<int>> neighbors;
  vector<vector<double>> graph;
  vector<Airport> airports;
};
