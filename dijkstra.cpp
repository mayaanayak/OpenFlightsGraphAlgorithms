#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool operator > (const Vertex& lhs, const Vertex& rhs) {
  if (lhs.weight_ > rhs.weight_) {
    return true;
  }
  return false;
}

// Returns an array indicating the previous-hop nodes on the shortest path from source to the given vertex
std::vector<int> Dijkstra::getPrev() {
  return prev_;
}

// Returns an an array for which dist_[v] "is the shortest distance from source to v when traveling via visited nodes only, or infinity if no such path exists."
std::vector<double> Dijkstra::getDist() {
  return dist_;
}

Dijkstra::Dijkstra(makeGraph mkg): mkg_(mkg) {}

void Dijkstra::runDijkstra(int source_id) {
    std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    std::vector<bool> seen;

    for (size_t i = 0; i < mkg_.getGraph().size(); i++) {
      dist_.push_back(std::numeric_limits<double>::max());
      prev_.push_back(-1);
      seen.push_back(false);
    }

    int source_idx_ = mkg_.getAirportIndex(source_id);
    
    dist_[source_idx_] = 0;

    for (size_t i = 0; i < mkg_.getNeighbors(source_idx_).size(); i++) {
        Vertex v(i, mkg_.edgeExists(source_idx_, i));
        q.push(v);
    }

    while (!q.empty()) {
      bool extracted = false;
      Vertex u = q.top();
      while (!extracted && !q.empty()) {
        u = q.top();
        if (!seen[u.idx_]) {
          extracted = true;
          seen[u.idx_] = true;
          break;
        }
        q.pop();
      }
      int min_idx = u.idx_;
      std::vector<int> neighbor_idxs;
      for (size_t i = 0; i < mkg_.getNeighbors(min_idx).size(); i++) {
        double distance = mkg_.routeDistance(min_idx, i);
        double alt = dist_[u.idx_] + mkg_.routeDistance(u.idx_, i);
        if (alt < dist_[i]) {
          dist_[i] = alt;
          prev_[i] = u.idx_;
          Vertex v(i, alt);
          q.push(v);
        }
      }
    }
}
