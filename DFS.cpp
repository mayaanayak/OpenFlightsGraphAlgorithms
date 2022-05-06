#include "DFS.h"
#include <map>
#include <queue>

using std::map;
using std::queue;

DFS::DFS(vector<vector<double>> graph_, vector<string> vertices_, vector<vector<string>> dset) : graph(graph_), vertices(vertices_), dv(dset) {
    
    //cout << __LINE__ << endl;
}

string DFS::getAirportIdFromName(std::string name) {
    for (size_t i = 0; i < dv.size(); i++) {
        if (dv[i][1].substr(1, dv[i][1].length() - 2) == name) {
            return dv[i][0];
        }
    }
    return "";
}


string DFS::getAirportIdFromIndex(int index) {
    return dv[index][0];
}

bool DFS::detect_cycle(vector<string> airportIds) {

    makeGraph mkg;
    mkg.populateGraph();
    queue<string> dfs;
    dfs.push(airportIds[0]);
    map<string, bool> visited;
    for (size_t i = 0; i < vertices.size(); i++) visited[getAirportIdFromName(vertices[i])] = false;
    visited[airportIds[0]] = true;
    while (!dfs.empty()) {
        string airportId = dfs.front();
        dfs.pop();

        int id = std::stoi(airportId);

        vector<int> neighborsIdx = mkg.getNeighbors(id);

        if (neighborsIdx.size() == 0) continue;

        vector<string> neighbors;
        for (int idx : neighborsIdx) {
            neighbors.push_back(getAirportIdFromIndex(idx));
        }

        for (string str : neighbors) {
            if (!visited[str]) {
                visited[str] = true;
            } else {
                return true;
            }
        }

        for (string str : neighbors) {
            dfs.push(str);
        }
    }
    return false;
}