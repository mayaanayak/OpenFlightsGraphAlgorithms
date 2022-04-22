#include "makeGraph.h"

using namespace std;

makeGraph::makeGraph() {
  parseData pdt;
  vector<vector<string>> dataVector = pdt.getDataVector("dataset/airports.dat");
  // populating our graph with default value 0 (no edges)
    graph.push_back(temp);
  }
  // populating map using the airportID as key and index as result.
    throw invalid_argument("AirportID is invalid. Not present in Airports.dat");
  }
=======
// return the vector of airports
Airport makeGraph::getAirports(int key) {
  Airport temp = airports[index];
  return temp;
}


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
>>>>>>> main
    } else {
      int sourceAirportIdx = getAirportIndex(stoi(dataVector[i][3]));
      int destinAirportIdx = getAirportIndex(stoi(dataVector[i][5]));
      // if airportID not found in the map.
      if (destinAirportIdx == -1 || sourceAirportIdx == -1) {
        continue;
      }
      // getting the latitude and longitude of each airport.
      double sourceAirLat = airports[sourceAirportIdx].latitude;
      double sourceAirLong = airports[sourceAirportIdx].longitude;
      double destinAirLat = airports[destinAirportIdx].latitude;
      double destinAirLong = airports[destinAirportIdx].longitude;
<<<<<<< HEAD
      // calling distance to get the distance between the airports.
      double km =  distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
      // storing the distance between the two airports at their respective
      // indexes.
      graph[sourceAirportIdx][destinAirportIdx] = km;
      //  cout << i << "<- index   km->" << km << endl;
=======
      double km = distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
      graph[sourceAirportIdx][destinAirportIdx] = km;

<<<<<<< HEAD
// Haversine formula to convert latitude and longitude between two points to km.
// lata is latitude of point A, latb is latitude of point B, longa is longitude
// of point A, longb is longitude of point B.
// returns the distance between the points in kilometre.
double makeGraph::distance(double lata, double latb, double longa,
                           double longb) {
=======
//Haversine formula to convert latitude and longitude between two points to km
double makeGraph::distance(double lata, double latb, double longa, double longb) {
>>>>>>> main
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

<<<<<<< HEAD
// populates the graph and then returns it.
vector<vector<double>> makeGraph::getGraph() {
    //populateGraph();
    return graph;
}

// adds an edge or flight between two airports.
// takes the source airportID and destination airportID as parameters.
void makeGraph::addEdge(int sourceAirID, int destAirID) {
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1) {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
  }
  double sourceAirLat = airports[sourceAirIdx].latitude;
  double sourceAirLong = airports[sourceAirIdx].longitude;
  double destinAirLat = airports[destAirIdx].latitude;
  double destinAirLong = airports[destAirIdx].longitude;
  double km =
      distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
  // cout << "here part 2" << endl;
  graph[sourceAirIdx][destAirIdx] = km;
}

// deletes an edge between two airports.
// takes the source airportID and destination airportID as parameters.
// sets the distance between them to zero.
void makeGraph::deleteEdge(int sourceAirID, int destAirID) {
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1) {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
    }
  graph[sourceAirIdx][destAirIdx] = 0;
}

// checks whether an edge exists between two airports i.e. if a flight exists
// between them. takes the source airportID and destination airportID as
// parameters. returns true if edge exists, false otherwise.
bool makeGraph::edgeExists(int sourceAirID, int destAirID) {
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1) {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
  }
  if (graph[sourceAirIdx][destAirIdx] > 0) {
    return true;
  } else {
    return false;
  }
}
=======
// first we need to go through routes.dat file, get the source airport and
// landing airport (if /N skill and go to next line) second we need to go
// through

>>>>>>> main
