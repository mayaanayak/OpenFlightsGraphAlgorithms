#include "makeGraph.h"

using namespace std;

makeGraph::makeGraph()
{
  parseData pdt;
  vector<vector<string>> dataVector = pdt.getDataVector("dataset/airports.dat");
  // populating our graph with default value 0 (no edges)
  for (size_t i = 0; i < dataVector.size(); i++)
  {
    vector<double> temp;
    for (size_t j = 0; j < dataVector.size(); j++)
    {
      temp.push_back(0.0);
    }
    graph.push_back(temp);
  }
  // populating map using the airportID as key and index as result.
  // Map<AirportID, int>.
  // cannot use airportID as index because airportID skips numbers.
  // populating a vector of airports, Airports is a struct which contain the
  // latitude and longitude.
  // populates the map neighbours which takes the index in the graph of each airport as the key and the vector of indexes of its neighbours as value.
  for (size_t i = 0; i < dataVector.size(); i++)
  {
    airport_index.insert(pair<int, int>((stoi(dataVector[i][0])), i));
    neighbors.insert(pair<int, int>(i, {}));
    Airport temp;
    temp.airportID = std::stoi(dataVector[i][0]);
    temp.latitude = std::stold(dataVector[i][6]);
    temp.longitude = std::stold(dataVector[i][7]);
    airports.push_back(temp);
  }
}

// key is the airportID.
// gets the index of that airportID from the map.
// return the Airport (containing latitude and longitude) from the Airports
// vector at that index.
Airport makeGraph::getAirports(int key)
{
  int index = getAirportIndex(key);
  if (index == -1)
  {
    throw invalid_argument("AirportID is invalid. Not present in Airports.dat");
  }
  Airport temp = airports[index];
  return temp;
}

// key is the airportID.
// searches for the airport ID in the map.
// return the index of that airport ID in the graph if found else -1.
int makeGraph::getAirportIndex(int key)
{
  int index = 0;
  // might need to use iterator if error
  if (airport_index.find(key) != airport_index.end())
  {
    index = airport_index.find(key)->second;
  }
  else
  {
    index = -1;
  }
  return index;
}

// function populates the graph.
// the index of the graph are the airports/nodes. The airportID is mapped to the
// index. the value of two indexes in the vector is the kilometre distance
// between the two airports.
void makeGraph::populateGraph()
{
  parseData pdt;
  vector<vector<string>> dataVector = pdt.getDataVector("dataset/routes.dat");
  for (size_t i = 0; i < dataVector.size(); i++)
  {
    // cout << dataVector.size() << endl;
    if (dataVector[i][3] == "\\N" || // Checking if any field is null
        dataVector[i][5] == "\\N")
    {
      //  cout << i << "here part 1 " << endl;
      continue;
    }
    else
    {
      // getting the index in the graph of each airport.
      int sourceAirportIdx = getAirportIndex(stoi(dataVector[i][3]));
      //   cout << stoi(dataVector[i][5]) << "<- destination val  source val ->"
      //  << stoi(dataVector[i][3]) << endl;
      int destinAirportIdx = getAirportIndex(stoi(dataVector[i][5]));
      // if airportID not found in the map.
      if (destinAirportIdx == -1 || sourceAirportIdx == -1)
      {
        continue;
      }
      // cout << sourceAirportIdx << "<- source   destination-> "
      //     << destinAirportIdx << endl;
      // getting the latitude and longitude of each airport.
      double sourceAirLat = airports[sourceAirportIdx].latitude;
      double sourceAirLong = airports[sourceAirportIdx].longitude;
      double destinAirLat = airports[destinAirportIdx].latitude;
      double destinAirLong = airports[destinAirportIdx].longitude;
      // calling distance to get the distance between the airports.
      double km =
          distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
      //  cout << "here part 2" << endl;
      // storing the distance between the two airports at their respective
      // indexes.
      if (graph[sourceAirportIdx][destinAirportIdx] == km)
      {
        continue;
      }
      else
      {
        graph[sourceAirportIdx][destinAirportIdx] = km;
      }
      //  cout << i << "<- index   km->" << km << endl;
      vector<int> temp = neighbors[sourceAirportIdx];
      temp.push_back(destinAirportIdx);
      neighbors[sourceAirportIdx] = temp;
    }
  }
}

// Haversine formula to convert latitude and longitude between two points to km.
// lata is latitude of point A, latb is latitude of point B, longa is longitude
// of point A, longb is longitude of point B.
// returns the distance between the points in kilometre.
double makeGraph::distance(double lata, double latb, double longa,
                           double longb)
{
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

// populates the graph and then returns it.
vector<vector<double>> makeGraph::getGraph()
{
  return graph;
}

// adds an edge or flight between two airports.
// takes the source airportID and destination airportID as parameters.
void makeGraph::addEdge(int sourceAirID, int destAirID)
{
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1)
  {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
  }
  double sourceAirLat = airports[sourceAirIdx].latitude;
  double sourceAirLong = airports[sourceAirIdx].longitude;
  double destinAirLat = airports[destAirIdx].latitude;
  double destinAirLong = airports[destAirIdx].longitude;
  double km =
      distance(sourceAirLat, destinAirLat, sourceAirLong, destinAirLong);
  if (graph[sourceAirIdx][destAirIdx] == km) {
    return;
  } else {
    graph[sourceAirIdx][destAirIdx] = km;
  }
  vector<int> temp = neighbors[sourceAirIdx];
  temp.push_back(destAirIdx);
  neighbors[sourceAirIdx] = temp;
}

// deletes an edge between two airports.
// takes the source airportID and destination airportID as parameters.
// sets the distance between them to zero.
void makeGraph::deleteEdge(int sourceAirID, int destAirID)
{
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1)
  {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
  }
  graph[sourceAirIdx][destAirIdx] = 0;
  vector<int> temp = neighbors[sourceAirIdx];
  auto it = find(temp.begin(), temp.end(), destAirIdx);
  if (it != temp.end()) {
    temp.erase(it);
    neighbors[sourceAirIdx] = temp;
  } else {
    return;
  }
}

// checks whether an edge exists between two airports i.e. if a flight exists
// between them. takes the source airportID and destination airportID as
// parameters. returns true if edge exists, false otherwise.
bool makeGraph::edgeExists(int sourceAirID, int destAirID)
{
  int sourceAirIdx = getAirportIndex(sourceAirID);
  int destAirIdx = getAirportIndex(destAirID);
  if (sourceAirIdx == -1 || destAirIdx == -1)
  {
    throw invalid_argument(
        "One or both of these Airport IDs do not exist in Airports.dat");
  }
  if (graph[sourceAirIdx][destAirIdx] > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// parameter is the index of the graph whose neighbours you want.
// returns the sorted vector which contains the indexes in the graph of the neighbours of that node.
vector<int> makeGraph::getNeighbors(int index)
{
  vector<int> ans;
  if (neighbors.find(index) != neighbors.end())
  {
    ans = neighbors.find(index)->second;
    sort(ans.begin(), ans.end());
    return ans;
  }
  else
  {
    throw invalid_argument("The index is not valid");
  }
}

//Returns the airportID if exists otherwise throws exception.
//parameter is index in the graph.
int makeGraph::getAirportID(int index) {
  if (index >= 0 && index < airports.size()) {
    return airports[index].airportID;
  } else {
    throw invalid_argument("Index out of bounds");
  }
}