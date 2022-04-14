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
        std::vector<std::vector<int>> graph_;
        int source_idx_;
        int source_id_;
        std::vector<int> prev_;
        std::unordered_map<int, int> idx_to_id_;
};

class Vertex {
  public:
    Vertex(int& idx, int& source_idx, std::vector<std::vector<int>>& graph): idx_(idx), source_idx_(source_idx), graph_(graph) {}
    friend bool operator > (const Vertex& lhs, const Vertex& rhs);

  private:
    int idx_;
    int source_idx_;
    std::vector<std::vector<int>> graph_;
};

struct Compare
{
    bool operator()(const Vertex& lhs, const Vertex& rhs)
    {
      if (lhs > rhs) {
        return true;
      }
      return false;
    }
};
