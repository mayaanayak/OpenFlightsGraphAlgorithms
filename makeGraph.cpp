#include "makeGraph.h"

using namespace std;

makeGraph::makeGraph() {
  parseData pdt;
  vector<vector<string>> dataVector = pdt.getDataVector("dataset/airports.dat");
  // populating our graph with default value 0 (no edges)
  for (unsigned i = 0; i < dataVector.size(); i++) {
    vector<double> temp;
    for (unsigned j = 0; j < dataVector.size(); j++) {
      temp.push_back(0.0);
    }
    graph.push_back(temp);
  }
  // populating map using the airportID as key and index as result.
  // Map<AirportID, int>.
  // populating the vector with longitude and latitude
  for (unsigned i = 0; i < dataVector.size(); i++) {
    airport_index.insert(pair<int, int>((stoi(dataVector[i][0])), i));
    Airport temp;
    //temp.airportID = std::stoi(dataVector[i][0]);
    temp.latitude = std::stold(dataVector[i][6]);
    temp.longitude = std::stold(dataVector[i][7]);
    airports.push_back(temp);
  }
}

// return the vector of airports
Airport makeGraph::getAirports(int key) {
  int index = getAirportIndex(key);
  Airport temp = airports[index];
  return temp;
}

// return the index of that airport ID in the graph
int makeGraph::getAirportIndex(int key) {
  // might need to use iterator if error
  int index = airport_index.find(key)->second;
  return index;
}

//code written no idea if it works need to test tomorrow
void makeGraph::populateGraph() {
  parseData pdt;
  vector<vector<string>> dataVector = pdt.getDataVector("dataset/routes.dat");
  for (unsigned i = 0; i < dataVector.size(); i++) {
    if (dataVector[i][3] == "\\N" || dataVector[i][5] == "\\N") { //can you compare \N?
      continue;
    } else {
      int sourceAirportIdx = getAirportIndex(stoi(dataVector[i][3]));
      int destinAirportIdx = getAirportIndex(stoi(dataVector[i][5]));
      double sourceAirLat = airports[sourceAirportIdx].latitude;
      double sourceAirLong = airports[sourceAirportIdx].longitude;
      double destinAirLat = airports[destinAirportIdx].latitude;
      double destinAirLong = airports[destinAirportIdx].longitude;
      double km = distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
      graph[sourceAirportIdx][destinAirportIdx] = km;
    }
  }
}

//Haversine formula to convert latitude and longitude between two points to km
double makeGraph::distance(double lata, double latb, double longa, double longb) {
  double lata_ = (M_PI / 180) * lata;
  double longa_ = (M_PI / 180) * longa;
  double latb_ = (M_PI / 180) * latb;
  double longb_ = (M_PI / 180) * longb;

  double radius = 6371;
  double dlong = longb_ - longa_;
  double dlat = latb_ - lata_;
  double ab =
      pow(sin(dlat / 2), 2) + cos(lata_) * cos(latb_) * pow(sin(dlong / 2), 2);
  double bc = 2 * atan2(sqrt(ab), sqrt(1 - ab));

  return radius * bc;
}

// first we need to go through routes.dat file, get the source airport and
// landing airport (if /N skill and go to next line) second we need to go
// through

