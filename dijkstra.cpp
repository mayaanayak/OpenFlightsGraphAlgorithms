#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool operator > (const Vertex& lhs, const Vertex& rhs) {
  std::vector<std::vector<int>> graph = lhs.graph_;
  int source_idx = lhs.source_idx_;
  if (graph[lhs.idx_][source_idx] > graph[rhs.idx_][source_idx]) {
    return true;
  }
  return false;
}

Dijkstra::Dijkstra(int source_id): source_id_(source_id), source_idx_(-1) {}

void Dijkstra::findFewestFlights() {
    // create vertex priority queue Q
    std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    //dist[v] ← INFINITY
    std::vector<int> temp_dist(INT_MAX, graph_.size());
    dist_ = temp_dist;
    // previous[v] := undefined
    std::vector<int> temp_prev(-1, graph_.size());
    prev_ = temp_prev;
    // Find the index corresponding to the given airport ID
    for (auto &i : idx_to_id_) {
      if (i.second == source_id_) {
         source_idx_ = i.first;
         break;
      }
    }
    // dist[source] := 0
    dist_[source_idx_] = 0;
    
    // for each vertex v in Graph.Vertices:
    for (int i = 0; i < graph_.size(); i++) {
      // Q.add_with_priority(v, dist[v])
        Vertex v(i, source_idx_, graph_);
        q.push(v);
    }
}
