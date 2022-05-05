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
        // Runs the Dijkstra algorithm with the inputted source airport
        std::vector<double> runDijkstra(int source_id);
        std::vector<int> getPrev();
        std::vector<double> getDist();
        // Returns the minimum distance of the path between a source airport and a destination airport as a double
        // source_id: The ID of the source airport
        // dest_id: The ID of the destination airport
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

// Custom comparator for the priority queue
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
