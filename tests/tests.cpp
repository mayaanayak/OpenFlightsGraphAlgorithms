#define CATCH_CONFIG_MAIN 

#include "../parseDat.h"
#include "../catch/catch.hpp"
#include "../dijkstra.h"
#include "../makeGraph.h"
#include "../DFS.h"
#include <typeinfo>
#include <math.h>       /* exp */
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>

using namespace std;

vector<vector<double>> graph;
vector<vector<string>> dv;
vector<string> vertices;

void populate() {
    makeGraph mkg;
    mkg.populateGraph();
    graph = mkg.getGraph();
    parseData pdt;
    dv = pdt.getDataVector("dataset/airports.dat");
    for (size_t i = 0; i < dv.size(); i++) vertices.push_back(dv[i][1].substr(1, dv[i][1].length() - 2));
}


TEST_CASE("Parse into data vector") {
    populate();
    // parseData pdt;
    // vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    int id = stoi(dv[0][0]);
    string airportName = dv[0][1].substr(1, 14);
    string city = dv[0][2].substr(1, 6);
    string country = dv[0][3].substr(1,16);
    string airportCode = dv[0][4].substr(1,3);
    long double latitude = stold(dv[0][6]);
    long double longitude = stold(dv[0][7]);


    double epsilon = 0.0000001f;

    REQUIRE(id == 1);
    REQUIRE(airportName == "Goroka Airport");
    REQUIRE(city == "Goroka");
    REQUIRE(country == "Papua New Guinea");
    REQUIRE(airportCode == "GKA");
    REQUIRE(fabs(latitude - (-6.081689834590001)) < epsilon);
    REQUIRE(fabs(longitude - (145.391998291)) < epsilon);
}


TEST_CASE("Parse into data vector, with parentheses in double inverted commas") {
    populate();
    // parseData pdt;
    // vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    string airportName = dv[652][1].substr(1, 30);
    REQUIRE(airportName == "Sandnessjøen Airport (Stokka)");
}

TEST_CASE("parse into data vector, with comma in double inverted commas") {
    populate();
    // parseData pdt;
    // vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    string airportName = dv[648][1].substr(1, 19);
    REQUIRE(airportName == "Moss Airport, Rygge");
}


TEST_CASE("edge/route exists") {
    makeGraph mkg;
    mkg.populateGraph();
    vector<vector<double>> graph = mkg.getGraph();
    bool edge = mkg.edgeExists(3043, 3131);
    //flight from Kolkata to Bengaluru exists
    REQUIRE(edge == true);   
}

TEST_CASE("graph populated") {
    makeGraph mkg;
    mkg.populateGraph();
    vector<vector<double>> graph = mkg.getGraph();
    //distance exists between Kolkata Banglore
    REQUIRE(graph[mkg.getAirportIndex(3043)][mkg.getAirportIndex(3131)] != 0);
}

TEST_CASE("route does not exist") {
    makeGraph mkg;
    mkg.populateGraph();
    vector<vector<double>> graph = mkg.getGraph();
    //no route exists between Kolkata and NYC
    REQUIRE(graph[mkg.getAirportIndex(3043)][mkg.getAirportIndex(3797)] == 0);
}

TEST_CASE("add edge works correctly") {
    //3797, 3043 
    makeGraph mkg;
    mkg.populateGraph();
    mkg.addEdge(3797, 3043);
    vector<vector<double>> graph = mkg.getGraph();
    //now edge exists between Kolkata and JFK
    REQUIRE(graph[mkg.getAirportIndex(3797)][mkg.getAirportIndex(3043)] > 0);
}


TEST_CASE("remove edge works correctly") {
    //3797, 3043 
    makeGraph mkg;
    mkg.populateGraph();
    mkg.deleteEdge(3043, 3131);
    vector<vector<double>> graph = mkg.getGraph();
    //now edge does exists between Kolkata and Banglore
    REQUIRE(graph[mkg.getAirportIndex(3043)][mkg.getAirportIndex(3131)] == 0);
}

TEST_CASE("test_distance 0")
{
    makeGraph mkg;
    double distance_ = mkg.distance(1,1,34,34);
    REQUIRE(distance_ == 0.0);
}
TEST_CASE("test_distance 1")
{
    makeGraph mkg;
 
    double epsilon = 0.0000001f;
    double distance_ = mkg.distance(1,34,30,45);
    REQUIRE(fabs(distance_ - 3987.7187763268) < epsilon);
}

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
    std::unordered_map<int, int> id_to_idx;
    std::unordered_map<int, vector<int>> neighbors;
    // The airport at index 0 has ID 50
    id_to_idx[50] = 0;
    neighbors[0] = {1, 2};
    // The airport at index 1 has ID 20
    id_to_idx[20] = 1;
    neighbors[1] = {0, 2, 3};
    // The airport at index 2 has ID 15
    id_to_idx[15] = 2;
    neighbors[2] = {0, 1, 3};
    // The airport at index 3 has ID 32
    id_to_idx[32] = 3;
    neighbors[3] = {1, 2};

    makeGraph mkg(id_to_idx, neighbors, graph);

    Dijkstra dijkstra(mkg);

    dijkstra.runDijkstra(50);
    std::vector<double> distance50 = dijkstra.getDist();
    std::vector<int> solution50{0, 5, 8, 7};
    for (size_t i = 0; i < distance50.size(); i++) {
        REQUIRE(distance50[i] == solution50[i]);
    }

    dijkstra.runDijkstra(20);
    std::vector<double> distance20 = dijkstra.getDist();
    std::vector<double> solution20{5, 0, 8, 2};
    for (size_t i = 0; i < distance20.size(); i++) {
        REQUIRE(distance20[i] == solution20[i]);
    }

    dijkstra.runDijkstra(15);
    std::vector<double> distance15 = dijkstra.getDist();
    std::vector<double> solution15{8, 8, 0, 6};
    for (size_t i = 0; i < distance15.size(); i++) {
        REQUIRE(distance15[i] == solution15[i]);
    }

    dijkstra.runDijkstra(32);
    std::vector<double> distance32 = dijkstra.getDist();
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
    std::unordered_map<int, int> id_to_idx;
    std::unordered_map<int, std::vector<int>> neighbors;
    // The airport at index 0 has ID 473
    id_to_idx[473] = 0;
    neighbors[0] = {1, 2, 5};
    // The airport at index 1 has ID 544
    id_to_idx[544] = 1;
    neighbors[1] = {0, 2, 3};
    // The airport at index 2 has ID 968
    id_to_idx[968] = 2;
    neighbors[2] = {0, 1, 3, 5};
    // The airport at index 3 has ID 213
    id_to_idx[213] = 3;
    neighbors[3] = {1, 2, 4};
    // The airport at index 4 has ID 750
    id_to_idx[750] = 4;
    neighbors[4] = {3, 5};
    // The airport at index 5 has ID 64
    id_to_idx[64] = 5;
    neighbors[5] = {0, 2, 4};

    makeGraph mkg(id_to_idx, neighbors, graph);
    Dijkstra dijkstra(mkg);

    dijkstra.runDijkstra(473);
    std::vector<double> solution473{0.0, 7.0, 9.0, 20.0, 20.0, 11.0};
    std::vector<double> distance473 = dijkstra.getDist();
    for (size_t i = 0; i < distance473.size(); i++) {
        REQUIRE(distance473[i] == solution473[i]);
    }  

    dijkstra.runDijkstra(544);
    std::vector<double> solution544{7.0, 0.0, 10.0, 15.0, 21.0, 12.0};
    std::vector<double> distance544 = dijkstra.getDist();
    for (size_t i = 0; i < distance544.size(); i++) {
        REQUIRE(distance544[i] == solution544[i]);
    }

    dijkstra.runDijkstra(968);
    std::vector<double> solution968{9.0, 10.0, 0.0, 11.0, 11.0, 2.0};
    std::vector<double> distance968 = dijkstra.getDist();
    for (size_t i = 0; i < distance968.size(); i++) {
        REQUIRE(distance968[i] == solution968[i]);
    }

    dijkstra.runDijkstra(213);
    std::vector<double> solution213{20.0, 15.0, 11.0, 0.0, 6.0, 13.0};
    std::vector<double> distance213 = dijkstra.getDist();
    for (size_t i = 0; i < distance213.size(); i++) {
        REQUIRE(distance213[i] == solution213[i]);
    }

    dijkstra.runDijkstra(750);
    std::vector<double> solution750{20.0, 21.0, 11.0, 6.0, 0.0, 9.0};
    std::vector<double> distance750 = dijkstra.getDist();
    for (size_t i = 0; i < distance750.size(); i++) {
        REQUIRE(distance750[i] == solution750[i]);
    }

    dijkstra.runDijkstra(64);
    std::vector<double> solution64{11.0, 12.0, 2.0, 13.0, 9.0, 0.0};
    std::vector<double> distance64 = dijkstra.getDist();
    for (size_t i = 0; i < distance64.size(); i++) {
        REQUIRE(distance64[i] == distance64[i]);
    }                                     
}

TEST_CASE("dijkstra_unconnected") {
    std::vector<std::vector<double>> graph {{0, 1.0, 1.0, 0.0, 0.0},
                                            {1.0, 0.0, 1.0, 0.0, 0.0},
                                            {1.0, 1.0, 0.0, 0.0, 0.0},
                                            {0.0, 0.0, 0.0, 0.0, 1.0},
                                            {0.0, 0.0, 0.0, 1.0, 0.0}};
    std::unordered_map<int, int> id_to_idx;
    std::unordered_map<int, vector<int>> neighbors;
    // The airport at index 0 has ID 50
    id_to_idx[50] = 0;
    neighbors[0] = {1, 2};
    // The airport at index 1 has ID 20
    id_to_idx[20] = 1;
    neighbors[1] = {0, 2};
    // The airport at index 2 has ID 15
    id_to_idx[15] = 2;
    neighbors[2] = {0, 1};
    // The airport at index 3 has ID 32
    id_to_idx[32] = 3;
    neighbors[3] = {4};
    // The airport at index 4 has ID 19
    id_to_idx[19] = 4;
    neighbors[4] = {3};

    makeGraph mkg(id_to_idx, neighbors, graph);
    Dijkstra dijkstra(mkg);

    dijkstra.runDijkstra(50);
    std::vector<double> solution{0.0, 1.0, 1.0, std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    std::vector<double> distance = dijkstra.getDist();
    for (size_t i = 0; i < distance.size(); i++) {
        REQUIRE(distance[i] == solution[i]);
    }
}

// We used the map on https://openflights.org/# and https://openflights.org/html/apsearch to create the real test cases.
TEST_CASE("dijkstra_real") {
    makeGraph mkg;
    mkg.populateGraph();
    Dijkstra dijkstra(mkg);
    // JFK to JFK
    // New York City to New York City
    REQUIRE(dijkstra.minDist(3797, 3797) == 0);
    // JFK to EZE
    // New York City to Buenos Aires
    REQUIRE(dijkstra.minDist(3797, 3988) == mkg.routeDistance(mkg.getAirportIndex(3797), mkg.getAirportIndex(3988)));
    // JFK to CCU
    // JFK -> DEL -> CCU
    // New York City to Kolkata
    double JFKtoDEL = mkg.routeDistance(mkg.getAirportIndex(3797), mkg.getAirportIndex(3093));
    double DELtoCCU = mkg.routeDistance(mkg.getAirportIndex(3093), mkg.getAirportIndex(3043));
    double JFKtoCCU = JFKtoDEL + DELtoCCU;
    REQUIRE(JFKtoCCU == dijkstra.minDist(3797, 3043));
    // AUX to PMW
    REQUIRE(dijkstra.minDist(4214, 7376) == mkg.routeDistance(mkg.getAirportIndex(4214), mkg.getAirportIndex(7376))); 
    // Dijkstra chooses shortest path
    // HKG -> SYD -> OOL
    // 3077 to 3361 to 3321
    double HKGtoSYD = mkg.routeDistance(mkg.getAirportIndex(3077), mkg.getAirportIndex(3361));
    double SYDtoOOL = mkg.routeDistance(mkg.getAirportIndex(3361), mkg.getAirportIndex(3321));
    double HKGtoOOL = HKGtoSYD + SYDtoOOL;
    REQUIRE(dijkstra.minDist(3077, 3321) < HKGtoOOL);
}

TEST_CASE("DFS round trip exists between three airports") {
    populate();
    DFS dfs(graph, vertices, dv);
    vector<string> vect = {"2997", "3043", "3093"};
    bool det = dfs.detect_cycle(vect);
    REQUIRE(det == true);
}

TEST_CASE("DFS round trip does not exist between three airports") {
    populate();
    DFS dfs(graph, vertices, dv);
    vector<string> vect = {"1993", "3043", "2001"};

    bool det = dfs.detect_cycle(vect);
    REQUIRE(det == false);
}

TEST_CASE("DFS round trip 10 airports") {
    populate();
    DFS dfs(graph, vertices, dv);
    vector<string> vect = {"2997", "3043", "3093", "3131", "3144", "2994", "1", "2", "3"};
    bool det = dfs.detect_cycle(vect);
    REQUIRE(det == true);
}

TEST_CASE("IDDFS_reachable") {
    makeGraph mkg;
    mkg.populateGraph();
    IDDFS iddfs(mkg);
    // Keflavík is reachable from Dar es Salaam with one stopover
    REQUIRE(iddfs.runIDDFS(1177, 16, 1));
    // Keflavík is not directly reachable from Dar es Salaam
    REQUIRE_FALSE(iddfs.runIDDFS(1177, 16, 0));
    // Chicago is not reachable from Accra with one stopover
    REQUIRE_FALSE(iddfs.runIDDFS(248, 3830, 1));
    // Chicago is not directly reachable from Accra
    REQUIRE_FALSE(iddfs.runIDDFS(248, 3830, 0));
}
