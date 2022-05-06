#include "makeGraph.h"
#include "dijkstra.h"
#include "iddfs.h"
#include "DFS.h"
#include "iddfs.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

int main() {
  
  bool done = false;
  while (!done) {
    int input = 0;
    cout << "Press 1 to find the shortest path between two airports" << endl;
    cout << "Press 2 to find if an airport is reachable from a given airport" << endl;
    cout << "Press 3 to find if given three or more airports is it possible to visit one or more of the airports more than once" << endl;
    cout << "Press 4 to quit" << endl;
    cout << "" << endl;
    cin >> input;
    cout << "" << endl;

    if (input == 4){
      done = true;
      break;
    } 

    parseData pdt;
    vector<vector<string>> dset = pdt.getDataVector("dataset/airports.dat");
    vector<string> vertices;
    for (size_t i = 0; i < dset.size(); i++) {
      vertices.push_back(dset[i][1]);
    }
    makeGraph mkg;
    mkg.populateGraph();
    vector<vector<double>> graph = mkg.getGraph();
    switch (input)
    {
      case 1: {
        int destID;
        int sourceID;

        cout << "Please input your starting airport ID (Unique OpenFlights identifier)" << endl;
        cin >> sourceID;
        cout << "Please input your destination airport ID (Unique OpenFlights identifier)" << endl;
        cin >> destID;
        Dijkstra dijk(mkg);
        double dist = dijk.minDist(sourceID, destID);
        cout << "" << endl;
        cout << "The shortest distance between " << sourceID << " and " << destID << " is " << dist << "km" << endl;
        cout << "" << endl;
        break;
      }
      case 2: {
        int flights;
        int destID;
        int sourceID;

        cout << "Please input your starting airport ID (Unique OpenFlights identifier)" << endl;
        cin >> sourceID;
        cout << "Please input your destination airport ID (Unique OpenFlights identifier)" << endl;
        cin >> destID;
        cout << "How many flights do you want to take at most between the two airports?" << endl;
        cin >> flights;

        IDDFS iddfs(mkg);
        bool ans = iddfs.runIDDFS(sourceID, destID, flights);
        if (ans == true) {
          cout << "" << endl;
          cout << "Yes the airport is reachable with the given number of flights" << endl;
          cout << "" << endl;
        } else {
          cout << "" << endl;
          cout << "The airport is not reachable with the given number of stopovers" << endl;
          cout << "" << endl;
        }
        break;
      }
      case 3: {
        int noAirports = 0;
        vector<string> airportIDs;
        while (noAirports < 3) {
        cout << "How many airports do you want to check? (minimum 3)" << endl;
        cin >> noAirports;
        }
        for (int i = 1; i <= noAirports; i++) {
          int id;
          cout << "Please enter airport number " << i << endl;
          cin >> id;
          airportIDs.push_back(std::to_string(id));
        }
        DFS dfs(graph, vertices, dset);
        bool ans = dfs.detect_cycle(airportIDs);
        if (ans == true) {
          cout << "" << endl;
          cout << "There is a roundtrip between the given airports" << endl;
          cout << "" << endl;
        } else {
          cout << "" << endl;
          cout << "There is no roundtrip between the given airports" << endl;
          cout << "" << endl;
        }
        break;
      }
      default: {
        break;
      }
    }
  }
  return 0;
}
