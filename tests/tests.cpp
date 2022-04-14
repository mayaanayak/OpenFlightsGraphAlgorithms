#include "../parseDat.h"
#include "../catch/catch.hpp"

using namespace std;


TEST_CASE("Parse into data vector") {
    parseData pdt;
    vector<vector<string>> parsed = pdt.getDataVector("dataset/airports.dat");
    int id = stoi(parsed[0][0]);
    string airportName = parsed[0][1];
    string city = parsed[0][2];
    string country = parsed[0][3];
    string airportCode = parsed[0][4];
    long double latitude = stold(parsed[0][6]);
    long double longitude = stold(parsed[0][7]);

    REQUIRE(id == 1);
    REQUIRE(airportName == "Goroka Airport");
    REQUIRE(city == "Goroka");
    REQUIRE(country == "Papua New Guinea");
    REQUIRE(airportCode == "GKA");
    REQUIRE(latitude == -6.082);
    REQUIRE(longitude == 145.391);
}