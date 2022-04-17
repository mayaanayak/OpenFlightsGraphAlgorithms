#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool operator > (const Vertex& lhs, const Vertex& rhs) {
  if (lhs.weight_ > rhs.weight_) {
    return true;
  }
  return false;
}

Dijkstra::Dijkstra(int source_id, std::vector<std::vector<double>>& graph, std::unordered_map<int, int>& idx_to_id): source_idx_(-1),  source_id_(source_id), graph_(graph), idx_to_id_(idx_to_id) {}

// Returns an array indicating the previous-hop nodes on the shortest path from source to the given vertex
std::vector<int> Dijkstra::getPrev() {
  return prev_;
}

// Returns an an array for which dist_[v] "is the shortest distance from source to v when traveling via visited nodes only, or infinity if no such path exists."
std::vector<double> Dijkstra::getDist() {
  return dist_;
}

void Dijkstra::runDijkstra() {
    std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    std::vector<bool> seen;

    for (size_t i = 0; i < graph_.size(); i++) {
      dist_.push_back(std::numeric_limits<double>::max());
      prev_.push_back(-1);
      seen.push_back(false);
    }

    // Find the index corresponding to the given airport ID
    bool found = false;
    for (auto &i : idx_to_id_) {
      if (i.second == source_id_) {
         source_idx_ = i.first;
         found = true;
         break;
      }
    }
    if (!found) {
      throw std::invalid_argument("Invalid airport ID.");
    }
    
    dist_[source_idx_] = 0;

    
    for (size_t i = 0; i < graph_.size(); i++) {
        Vertex v(i, graph_[source_idx_][i]);
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
      for (size_t i = 0; i < graph_[min_idx].size(); i++) {
        double distance = graph_[min_idx][i];
        if (distance == 0) continue;
        double alt = dist_[u.idx_] + graph_[u.idx_][i];
        if (alt < dist_[i]) {
          dist_[i] = alt;
          prev_[i] = u.idx_;
          Vertex v(i, alt);
          q.push(v);
        }
      }
    }
}
