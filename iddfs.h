#pragma once
#include "makeGraph.h"
#include <vector>
#include <limits>

class IDDFS {
    public:
        IDDFS(makeGraph mkg);
        bool runIDDFS(int start, int dest, int max_depth);
        std::pair<int, bool> DLS(int startIdx, int destIdx, int limit);
    private:
        makeGraph mkg_;
};
