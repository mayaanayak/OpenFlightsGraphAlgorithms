#include "../parseDat.h"
#include "../catch/catch.hpp"
#include "../makeGraph.h"
#include <typeinfo>
#include <math.h>       /* exp */
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>

using namespace std;


TEST_CASE("Parse into data vector") {
    parseData pdt;
    vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    int id = stoi(parsed[0][0]);
    string airportName = parsed[0][1].substr(1, 14);
    string city = parsed[0][2].substr(1, 6);
    string country = parsed[0][3].substr(1,16);
    string airportCode = parsed[0][4].substr(1,3);
    long double latitude = stold(parsed[0][6]);
    long double longitude = stold(parsed[0][7]);


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
    parseData pdt;
    vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    string airportName = parsed[652][1].substr(1, 30);
    REQUIRE(airportName == "Sandnessjøen Airport (Stokka)");
}

TEST_CASE("parse into data vector, with comma in double inverted commas") {
    parseData pdt;
    vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    string airportName = parsed[648][1].substr(1, 19);
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
