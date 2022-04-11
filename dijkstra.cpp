#include "dijkstra.h"

// We referenced the following pseudocode in implementing Dijkstra's algorithm:
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

Dijkstra::Dijkstra(int source_id): source_id_(source_id), source_idx_(-1) {}

void Dijkstra::findFewestFlights() {
    // create vertex priority queue Q
    std::priority_queue<int> q;
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

    // std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> q(Compare);
    //std::priority_queue<Foo, std::vector<Foo>, std::function<bool(Foo, Foo)>> pq(Compare);
    std::priority_queue<int, std::vector<int>, std::function<bool(const int &, const int &)>> q(Compare);

    // for each vertex v in Graph.Vertices:
    for (size_t i = 0; i < graph_.size(); i++) {
        // Q.add_with_priority(v, dist[v])
        q.push(graph_[i][0]);
    }
}


