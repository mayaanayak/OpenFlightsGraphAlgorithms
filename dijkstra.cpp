#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool operator > (const Vertex& lhs, const Vertex& rhs) {
  if (lhs.weight_ > rhs.weight_) {
    return true;
  }
  return false;
}

// Returns an array indicating the previous-hop nodes on the shortest path from source to the given vertex.
std::vector<int> Dijkstra::getPrev() {
  return prev_;
}

// Returns an an array for which dist_[v] "is the shortest distance from source to v when traveling via visited nodes only, or infinity if no such path exists."
std::vector<double> Dijkstra::getDist() {
  return dist_;
}

Dijkstra::Dijkstra(makeGraph mkg): mkg_(mkg) {}

void Dijkstra::runDijkstra(int source_id) {
    // Clears the distance, previous, and seen vectors in case dijkstra was already run.
    dist_.clear();
    prev_.clear();
    seen_.clear();

    std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    std::vector<bool> seen;

    // Sets the distances for all of the vertices to infinity.
    for (size_t i = 0; i < mkg_.getGraph().size(); i++) {
      dist_.push_back(std::numeric_limits<double>::max());
      prev_.push_back(-1);
      seen.push_back(false);
    }

    // Finds the source index and sets the distance at that position to 0
    int source_idx_ = mkg_.getAirportIndex(source_id);
    dist_[source_idx_] = 0;

    // Finds the neighbors of the source_idx and pushes them to the queue
    std::vector<int> neighbors = mkg_.getNeighbors(source_idx_);

    for (size_t i = 0; i < neighbors.size(); i++) {
      Vertex v(neighbors[i], mkg_.routeDistance(source_idx_, neighbors[i]));
      q.push(v);
    }

    // Updates the distances of neighbors of the source vertex 
    for (size_t i = 0; i < neighbors.size(); i++) {
      dist_[neighbors[i]] = mkg_.routeDistance(source_idx_, neighbors[i]);
      prev_[neighbors[i]] = source_idx_;
      Vertex v(neighbors[i], dist_[neighbors[i]]);
      q.push(v);
    }

    while (!q.empty()) {
      // Extract the topmost node from the queue that has not already been seen (seen exists to implement lazy deletion)
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
      // Update the distances as needed
      int min_idx = u.idx_;
      std::vector<int> neighbors = mkg_.getNeighbors(min_idx);
      for (size_t i = 0; i < neighbors.size(); i++) {
        double distance = mkg_.routeDistance(min_idx, neighbors[i]);
        double alt = dist_[u.idx_] + mkg_.routeDistance(u.idx_, neighbors[i]);
        if (alt < dist_[neighbors[i]]) {
          dist_[neighbors[i]] = alt;
          prev_[neighbors[i]] = min_idx;
          Vertex v(neighbors[i], alt);
          q.push(v);
        }
      }
    }
}