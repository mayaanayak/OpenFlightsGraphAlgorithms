#pragma once
#include <vector>
#include <limits>
#include <unordered_map>
#include <queue>

class Dijkstra {
    public:
        Dijkstra(int source_id);
        void findFewestFlights();
        std::vector<double> dist_;

    private:
        std::vector<std::vector<double>> graph_;
        int source_idx_;
        int source_id_;
        std::vector<int> prev_;
        std::vector<bool> seen_;
        std::unordered_map<int, int> idx_to_id_;
};

struct Vertex {
  Vertex(size_t idx, double weight): idx_(idx), weight_(weight) {}
  friend bool operator > (const Vertex& lhs, const Vertex& rhs);
  int idx_;
  double weight_;
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
