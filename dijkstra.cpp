#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

bool operator > (const Vertex& lhs, const Vertex& rhs) {
  if (lhs.weight_ > rhs.weight_) {
    return true;
  }
  return false;
}

Dijkstra::Dijkstra(int source_id): source_id_(source_id), source_idx_(-1) {}

void Dijkstra::findFewestFlights() {
    // create vertex priority queue Q
    std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    //dist[v] ← INFINITY
    std::vector<double> temp_dist(std::numeric_limits<double>::max(), graph_.size());
    dist_ = temp_dist;
    std::vector<bool> seen(false, graph_.size());

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
        Vertex v(i, graph_[source_idx_][i]);
        q.push(v);
    }

    // while Q is not empty
    while (!q.empty()) {
      bool extracted = false;
      // u ← Q.extract_min()
      Vertex u = q.top();
      while (!extracted) {
        if (!seen[u.idx_]) {
          extracted = true;
        }
        q.pop();
      }
      seen[u.idx_] = true;
      int min_idx = u.idx_;
      // for each neighbor v of u
      std::vector<int> neighbor_idxs;
      for (int i = 0; i < graph_[min_idx].size(); i++) {
        double distance = graph_[min_idx][i];
        if (distance == 0) continue;
        // alt ← dist[u] + Graph.Edges(u, v)
        double alt = dist_[u.idx_] + graph_[u.idx_][i];
        // if alt < dist[v]
        if (alt < dist_[i]) {
          // dist[v] ← alt
          dist_[i] = alt;
          //prev[v] ← u
          prev_[i] = u.idx_;
          Vertex v(i, alt);
          // Q.decrease_priority(v, alt)
          q.push(v);
        }
      }
    }
}
