#pragma once
#include <vector>
#include <cstddef>
#include <climits>
#include <unordered_map>
#include <queue>

class Dijkstra {
    public:
        Dijkstra(int source_id);
        void findFewestFlights();

    private:
        int source_id_;
        std::vector<int> dist_;
        std::vector<int> prev_;
        std::vector<std::vector<int>> graph_;
        std::unordered_map<int, int> idx_to_id_;
};