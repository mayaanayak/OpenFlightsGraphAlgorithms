#pragma once
#include <vector>
#include <cstddef>
#include <climits>
#include <unordered_map>
#include <queue>
#include <functional>

class Dijkstra {
    public:
        Dijkstra(int source_id);
        void findFewestFlights();
        std::vector<int> dist_;

    private:
        int source_id_;
        int source_idx_;
        std::vector<int> prev_;
        std::vector<std::vector<int>> graph_;
        std::unordered_map<int, int> idx_to_id_;

        bool Compare(const int& lhs, const int& rhs) {
          if (graph_[lhs][source_idx_] > graph_[rhs][source_idx_]) {
            return true;
          }
          return false;
        }
};