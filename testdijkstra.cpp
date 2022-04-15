#include "cs225/catch/catch.hpp"
#include "dijkstra.h"

TEST_CASE("test_priority_queue")
{
	std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    Vertex a(0, 10.0);
    Vertex b(0, 11.0);
    Vertex c(2, 5.0);
    Vertex result = q.top();
    q.pop();
    REQUIRE(result.weight_ == 5.0);
    q.pop();
    REQUIRE(result.weight_ == 10.0);
    q.pop();
    REQUIRE(result.weight_ == 11.0);
}
