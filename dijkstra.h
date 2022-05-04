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
        std::vector<double> runDijkstra(int source_id);
        std::vector<int> getPrev();
        std::vector<double> getDist();
        double minDist(int source_id, int dest_id);

    private:
        makeGraph mkg_;
        std::vector<double> dist_;
        int source_id_;
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
