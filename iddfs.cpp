#include "iddfs.h"

using namespace std;

bool IDDFS(int start, int dest, int max_depth) {
    makeGraph mkg;
    mkg.populateGraph();
    int startIdx = mkg.getAirportIndex(start);
    int destIdx = mkg.getAirportIndex(dest);
    for (int i = 0; i <= max_depth; i++) {
        if (DLS(startIdx, destIdx, i, mkg)) {
            return true;
        }
    }
    return false;
}

bool DLS(int startIdx, int destIdx, int limit, makeGraph mkg) {
    if (startIdx == destIdx) return true;
    if (limit <= 0) return false;
    vector<int> neighbors = mkg.getNeighbors(startIdx);
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (DLS(i, destIdx, limit - 1, mkg)) return true;
    }
    return false;
}