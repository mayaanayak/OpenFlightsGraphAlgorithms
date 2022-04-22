#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"
#include "../dijkstra.h"

// clang++ tests/testdijkstra.cpp dijkstra.cpp -std=c++14 -stdlib=libc++ -lc++abi -lm -o dijkstra

TEST_CASE("test_priority_queue")
{
	std::priority_queue<Vertex, std::vector<Vertex>, Compare> q;
    Vertex a(0, 10.4);
    Vertex b(0, 11.3);
    Vertex c(2, 5.2);
    q.push(a);
    q.push(b);
    q.push(c);
    Vertex result = q.top();
    q.pop();
    REQUIRE(result.weight_ == 5.2);
    result = q.top();
    q.pop();
    REQUIRE(result.weight_ == 10.4);
    result = q.top();
    q.pop();
    REQUIRE(result.weight_ == 11.3);
}

TEST_CASE("test_dijkstra_small")
{
    // Represents the following graph: https://www.freecodecamp.org/news/content/images/2020/06/image-126.png
    std::vector<std::vector<double>> graph { { 0.0, 5.0, 8.0, 0.0 },
                                             { 5.0, 0.0, 9.0, 2.0 },
                                             { 8.0, 9.0, 0.0, 6.0 },
                                             { 0.0, 2.0, 6.0, 0.0 }};
    std::unordered_map<int, int> idx_to_id;
    // The airport at index 0 has ID 50
    idx_to_id[0] = 50;
    // The airport at index 1 has ID 20
    idx_to_id[1] = 20;
    // The airport at index 2 has ID 15
    idx_to_id[2] = 15;
    // The airport at index 3 has ID 32
    idx_to_id[3] = 32;

    Dijkstra dijkstra50(50, graph, idx_to_id);
    dijkstra50.runDijkstra();
    std::vector<double> distance50 = dijkstra50.getDist();
    std::vector<int> solution50{0, 5, 8, 7};
    for (size_t i = 0; i < distance50.size(); i++) {
        REQUIRE(distance50[i] == solution50[i]);
    }

    Dijkstra dijkstra20(20, graph, idx_to_id);
    dijkstra20.runDijkstra();
    std::vector<double> distance20 = dijkstra20.getDist();
    std::vector<double> solution20{5, 0, 8, 2};
    for (size_t i = 0; i < distance20.size(); i++) {
        REQUIRE(distance20[i] == solution20[i]);
    }

    Dijkstra dijkstra15(15, graph, idx_to_id);
    dijkstra15.runDijkstra();
    std::vector<double> distance15 = dijkstra15.getDist();
    std::vector<double> solution15{8, 8, 0, 6};
    for (size_t i = 0; i < distance15.size(); i++) {
        REQUIRE(distance15[i] == solution15[i]);
    }

    Dijkstra dijkstra32(32, graph, idx_to_id);
    dijkstra32.runDijkstra();
    std::vector<double> distance32 = dijkstra32.getDist();
    std::vector<double> solution32{7, 2, 6, 0};
    for (size_t i = 0; i < distance32.size(); i++) {
        REQUIRE(distance32[i] == solution32[i]);
    }
}

TEST_CASE("test_dijkstra_complex")
{
    // Represents the following graph: https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif
    std::vector<std::vector<double>> graph { { 0.0, 7.0, 9.0, 0.0, 0.0,14.0 },
                                             { 7.0, 0.0,10.0,15.0, 0.0, 0.0 },
                                             { 9.0,10.0, 0.0,11.0, 0.0, 2.0 },
                                             { 0.0,15.0,11.0, 0.0, 6.0, 0.0 },
                                             { 0.0, 0.0, 0.0, 6.0, 0.0, 9.0 },
                                             {14.0, 0.0, 2.0, 0.0, 9.0, 0.0 } }; 
    std::unordered_map<int, int> idx_to_id;
    // The airport at index 0 has ID 473
    idx_to_id[0] = 473;
    // The airport at index 1 has ID 544
    idx_to_id[1] = 544;
    // The airport at index 2 has ID 968
    idx_to_id[2] = 968;
    // The airport at index 3 has ID 213
    idx_to_id[3] = 213;
    // The airport at index 4 has ID 750
    idx_to_id[4] = 750;
    // The airport at index 5 has ID 64
    idx_to_id[5] = 64;

    Dijkstra dijkstra473(473, graph, idx_to_id);
    dijkstra473.runDijkstra();
    std::vector<double> solution473{0.0, 7.0, 9.0, 20.0, 20.0, 11.0};
    std::vector<double> distance473 = dijkstra473.getDist();
    for (size_t i = 0; i < distance473.size(); i++) {
        REQUIRE(distance473[i] == solution473[i]);
    }  

    Dijkstra dijkstra544(544, graph, idx_to_id);
    dijkstra544.runDijkstra();
    std::vector<double> solution544{7.0, 0.0, 10.0, 15.0, 21.0, 12.0};
    std::vector<double> distance544 = dijkstra544.getDist();
    for (size_t i = 0; i < distance544.size(); i++) {
        REQUIRE(distance544[i] == solution544[i]);
    }

    Dijkstra dijkstra968(968, graph, idx_to_id);
    dijkstra968.runDijkstra();
    std::vector<double> solution968{9.0, 10.0, 0.0, 11.0, 11.0, 2.0};
    std::vector<double> distance968 = dijkstra968.getDist();
    for (size_t i = 0; i < distance968.size(); i++) {
        REQUIRE(distance968[i] == solution968[i]);
    }

    Dijkstra dijkstra213(213, graph, idx_to_id);
    dijkstra213.runDijkstra();
    std::vector<double> solution213{20.0, 15.0, 11.0, 0.0, 6.0, 13.0};
    std::vector<double> distance213 = dijkstra213.getDist();
    for (size_t i = 0; i < distance213.size(); i++) {
        REQUIRE(distance213[i] == solution213[i]);
    }

    Dijkstra dijkstra750(750, graph, idx_to_id);
    dijkstra750.runDijkstra();
    std::vector<double> solution750{23.0, 21.0, 11.0, 6.0, 0.0, 9.0};
    std::vector<double> distance750 = dijkstra750.getDist();
    for (size_t i = 0; i < distance750.size(); i++) {
        REQUIRE(distance750[i] == solution750[i]);
    }

    Dijkstra dijkstra64(64, graph, idx_to_id);
    dijkstra64.runDijkstra();
    std::vector<double> solution64{11.0, 12.0, 2.0, 13.0, 9.0, 0.0};
    std::vector<double> distance64 = dijkstra64.getDist();
    for (size_t i = 0; i < distance64.size(); i++) {
        REQUIRE(distance64[i] == distance64[i]);
    }                                     
}
