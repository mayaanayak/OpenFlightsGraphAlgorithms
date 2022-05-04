#pragma once
#include "makeGraph.h"
#include <vector>

using namespace std;

class IDDFS {
    public:
        IDDFS(makeGraph mkg);
        bool runIDDFS(int start, int dest, int max_stopovers);
        bool DLS(int startIdx, int destIdx, int limit, makeGraph mkg);
    private:
        makeGraph mkg_;
};
