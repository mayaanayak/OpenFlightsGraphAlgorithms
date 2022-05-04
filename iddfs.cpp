// Referenced Wikipedia pseudocode

#include "iddfs.h"

IDDFS::IDDFS(makeGraph mkg): mkg_(mkg) {}

bool IDDFS::runIDDFS(int start, int dest, int max_flights) {
    int startIdx = mkg_.getAirportIndex(start);
    int destIdx = mkg_.getAirportIndex(dest);
    for (int i = 0; i <= max_flights; i++) {
        std::pair<int, bool> foundremaining = DLS(startIdx, destIdx, i);
        int found = foundremaining.first;
        bool remaining = foundremaining.second;
        if (found != std::numeric_limits<int>::max()) {
            return true;
        }
        if (!remaining) {
            return false;
        }
    }
    return false;
}

std::pair<int, bool> IDDFS::DLS(int startIdx, int destIdx, int limit) {
    if (limit == 0) {
        if (startIdx == destIdx) {
            return (std::pair<int,bool>(startIdx,true));
        } else {
            return (std::pair<int, bool>(std::numeric_limits<int>::max(), true));
        }
    }
    bool any_remaining = false;
    std::vector<int> neighbor_indices = mkg_.getNeighbors(startIdx);
    for (size_t i = 0; i < neighbor_indices.size(); i++) {
        int child = neighbor_indices[i];
        std::pair<int, bool> foundremaining = DLS(child, destIdx, limit - 1);
        int found = foundremaining.first;
        bool remaining = foundremaining.second;
        if (found != std::numeric_limits<int>::max()) {
            return (std::pair<int, bool>(found, true));
        }
        if (remaining) {
            any_remaining = true;
        }
    }
    return (std::pair<int, bool>(std::numeric_limits<int>::max(), any_remaining));
}

