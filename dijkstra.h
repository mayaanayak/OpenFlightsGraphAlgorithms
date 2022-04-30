#pragma once
#include <vector>
#include <limits>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <map>
#include "makeGraph.h"

class Dijkstra {
    public:
        Dijkstra(makeGraph mkg);
        void runDijkstra(int source_id);
        std::vector<int> getPrev();
        std::vector<double> getDist();

    private:
        makeGraph mkg_;
        std::vector<double> dist_;
        int source_idx_;
        std::vector<int> prev_;
        std::vector<bool> seen_;
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
