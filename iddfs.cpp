#include "iddfs.h"
// Referenced Geeks4Geeks pseudocode

using namespace std;

IDDFS::IDDFS(makeGraph mkg): mkg_(mkg) {}

bool IDDFS::runIDDFS(int start, int dest, int max_stopovers) {
    int startIdx = mkg_.getAirportIndex(start);
    int destIdx = mkg_.getAirportIndex(dest);
    for (int i = 0; i <= max_stopovers; i++) {
        if (DLS(startIdx, destIdx, i, mkg_)) {
            return true;
        }
    }
    return false;
}

bool IDDFS::DLS(int startIdx, int destIdx, int limit) {
    if (startIdx == destIdx) return true;
    if (limit <= 0) return false;
    vector<int> neighbors = mkg_.getNeighbors(startIdx);
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (DLS(i, destIdx, limit - 1)) return true;
    }
    return false;
}
