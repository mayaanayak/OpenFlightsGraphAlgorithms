#pragma once
#include "makeGraph.h"
#include <vector>

using namespace std;


bool IDDFS(int start, int dest, int max_depth);
bool DLS(int startIdx, int destIdx, int limit, makeGraph mkg);
