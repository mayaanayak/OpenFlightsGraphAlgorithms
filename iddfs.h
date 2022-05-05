#pragma once
#include "makeGraph.h"
#include <vector>
#include <limits>

class IDDFS {
    public:
        IDDFS(makeGraph mkg);
        // Returns whether a destination airport is reachable from a source airport given a maximum number of flights
        // start: the source airport ID
        // dest: the destination airport ID
        // max_flights: the maximum number of flights the user is willing to take
        bool runIDDFS(int start, int dest, int max_flights);
    private:
        // IDDFS recursive helper function
        std::pair<int, bool> DLS(int startIdx, int destIdx, int limit);
        makeGraph mkg_;
};
