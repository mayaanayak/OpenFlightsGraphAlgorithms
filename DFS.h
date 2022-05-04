
#include "makeGraph.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

using std::cout;
using std::endl;
using std::map;
using std::queue;
using std::string;
using std::vector;

class DFS {
    public:
        DFS(vector<vector<double>> graph_, vector<string> vertices_, vector<vector<string>> dset);
        bool detect_cycle(vector<string> airports); 
    private:
        string getAirportIdFromName(std::string name);
        string getAirportFromIndex(int index);
        vector<vector<double>> graph;
        vector<string> vertices;
        vector<vector<string>> dv;
};