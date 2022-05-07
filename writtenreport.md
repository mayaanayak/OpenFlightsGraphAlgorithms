# harsha4-saraza2-kushal2-mayan3 Final Project

## Leading Question
When we started this project our leading question was whether we can utilize this dataset and the algorithms provided to find the shortest possible path between two airports, if it is possible to travel between two airports within a certain number of flights, and if given three or more airports is it possible to visit an airport more than once. We approached these questions by creating an adjacency matrix undirected weighted graph, with the airports as vertices and distance between connected airports as the edges, and an unordered map of neighbors of each vertex. We then implemented the Djikstra, IDDFS and DFS algorithm on the graph to get the answers to our questions. Overall, we were successful in implementing our project while simultaneously discovering how important graphs are in representing datasets and the most efficient methods to extract useful data from them.

## DFS
We employ DFS to determine that given three or more airports, is it possible to visit an airport more than once. This can in fact be used to determine if a round trip exists between two airports, which might in fact help users plan a trip. 

We first verified the correctness of DFS using small test cases, (3 airports). The test case is given below. DFS works by calling the public function on a set of airport ids, yeildig true if a cycle is detected.

```C++ 
    bool detect_cycle(vector<string> airportIds);
```

The test case below checks for 3 given indian airports, which are sure to have a round trip between them, and yeilds the desired output i.e. true.

```C++
    DFS dfs(graph, vertices, dv);
    vector<string> vect = {"2997", "3043", "3093"};
    bool det = dfs.detect_cycle(vect);
    REQUIRE(det == true);
```

Next, to check if there is no round trip between the given airports, or a cycle between them, we use the below mentioned test case. The airports are from 3 different continents, with no round trip existing between them. Upon running DFS, we get false, which is what we expect.

```C++
    TEST_CASE("DFS round trip does not exist between three airports") {
    populate();
    DFS dfs(graph, vertices, dv);
    vector<string> vect = {"1993", "3043", "2001"};

    bool det = dfs.detect_cycle(vect);
    REQUIRE(det == false);
    }
```

In order to check if DFS works on bigger test cases, we used a set of ten airports and see if it yeilds our desired output. As expected, the output works correctly, passing all DFS test cases, showing that there is a round trip 

```C++
    TEST_CASE("DFS round trip 10 airports") {
        populate();
        DFS dfs(graph, vertices, dv);
        vector<string> vect = {"2997", "3043", "3093", "3131", "3144", "2994", "1", "2", "3"};
        bool det = dfs.detect_cycle(vect);
        REQUIRE(det == true);
    }
```

## Dijkstra
We employ the Dijkstra algorithm to determine the minimum distance between two airports.

We first verified the correctness of Dijkstra using small, artificial test cases, such as those shown below. We constructed our variant of an adjacency matrix (a 0 entry indicates the lack of an edge between two airports, while a non-zero entry indicates the distance between two airports) for each of these test cases. We arbitrarily assigned each node IDs, and we created a special makeGraph constructor to enable these test cases. Since these graphs are relatively small, it was feasible to test that the minimum distance from every node to every other node was what we expected:

Graph (source: freeCodeCamp)| Corresponding test case
:-------------------------:|:-------------------------:
<img src="WR1.png" width="500"/>  |  <img src="WR3.PNG" width="500"/>

Graph (source: Wikimedia Commons)| Corresponding test case
:-------------------------:|:-------------------------:
<img src="WR2.gif" width="500"/>  |  <img src="WR4.PNG" width="500"/>

We then tested our algorithm on the graph itself. Determining the minimum distance between two airports was challenging, given that there were often several possible routes between two airports which did not have a direct flight between them. We identified four possible scenarios:

1) The user wants to determine the minimum distance between an Airport A and Airport A (itself). We tested this scenario by verifying that Dijkstra outputted 0 when the user inputted the airport ID corresponding to JFK as both the source and destination ID.
```C++ 
REQUIRE(dijkstra.minDist(3797, 3797) == 0);
```
2) The user wants to determine the minimum distance between an Airport A and an Airport B, where there is a direct flight between Airport A and Airport B. We tested this scenario by verifying that the Dijkstra outputted the orthodromic distance between JFK and EZE when the user inputted the airport ID corresponding to JFK as the source airport and the airport ID corresponding to EZE as the destination airport.
```C++ 
REQUIRE(dijkstra.minDist(3797, 3988) == mkg.routeDistance(mkg.getAirportIndex(3797), mkg.getAirportIndex(3988)));
```
3) The user wants to determine the minimum distance between Airport A and Airport B. There is no direct flight between Airport A and Airport B, but Airport B is somehow reachable from Airport A (i.e. Airport B is reachable from Airport A with some number of stopovers). We tested this scenario by verifying that Dijkstra outputted the sum of the orthodromic distance between JFK and DEL and the orthodromic distance between DEL and CCU when the user inputted the airport ID corresponding to JFK as the source airport and the airport ID corresponding to CCU as the destination airport.
```C++ 
double JFKtoDEL = mkg.routeDistance(mkg.getAirportIndex(3797), mkg.getAirportIndex(3093));
double DELtoCCU = mkg.routeDistance(mkg.getAirportIndex(3093), mkg.getAirportIndex(3043));
double JFKtoCCU = JFKtoDEL + DELtoCCU;
REQUIRE(JFKtoCCU == dijkstra.minDist(3797, 3043));
```
4) The user wants to determine the minimum distance between Airport A and Airport B, where Airport B is not reachable from Airport A. We tested this scenario by verifying that Dijkstra outputted the maximum double value when the user inputted the airport ID corresponding to GEA as the source airport and the airport ID corresponding to CCU as the destination airport.
```C++ 
REQUIRE(dijkstra.minDist(2001, 3043) == std::numeric_limits<double>::max());
```

## IDDFS
We use IDDFS to determine whether it was possible to reach from one airport to another within the number of flights defined by the user. The user inputs the destination airport OpenFlights ID, the source airport OpenFlights ID, and the number of flights they want to take to reach their destination. We implement IDDFS by running a loop until the depth/number of flights and check each neighbor until the source node is found/not found. 

When we first implemented the algorithm, IDDFS was running slower than the desired runtime; hoever, we pinpointed the problem to the fact that with each iteration of the depth, the algorithm was restarting at the root. Our runtime significantly improved after we handled that error by making sure the algorithm restarted at the last explored node.

We verified the correctness of IDDFS through local test cases stated below. We formulated these test cases by looking at the dataset, specifically routes.dat, and checking whether a direct or non-direct flight exists between two airports. If it was the latter, we determined how many flights it should take to reach from the source airport to the destination airport by looking at routes and then corroborated our calculations with the IDDFS output. We checked for three cases within our test case:

1. We checked if the program outputs false if a depth of 0 (which signifies that no number of flights were defined) is inputted. This test case was used mainly to test the functionality of our algorithm rather than user input. In reality, the user is restricted from inputting 0 in main and can only input a minimum value of 1.

```C++
 REQUIRE_FALSE(iddfs.runIDDFS(3093, 3043, 0));
 ```
 
 2. We checked if an airport can be reached from another airport within one flight i.e. a direct flight. This would be possible if the flight is defined in routes.dat. We also checked if a direct flight is not possible i.e. the depth is greater than 1. This would only be possible if the flight is not defined in routes.dat and if that is the case, the program returns false.

```C++
 // Kolkata is directly reachable from Delhi
    REQUIRE(iddfs.runIDDFS(3093, 3043, 1));
 // Keflavík is not directly reachable from Dar es Salaam
    REQUIRE_FALSE(iddfs.runIDDFS(1177, 16, 1));
```

3. We checked if an airport is reachable from another airport using two flights i.e. with one stopover. This would be possible if the two airports share a similar neighbor i.e. the stopover airport has an edge in the graph with the source and destination airport. For the result to be true, the user has to input >=2 number of flights otherwise the program will output false.

```C++
    //Kochi is not directly reachable from Multan
    REQUIRE_FALSE(iddfs.runIDDFS(2214, 3136, 1));
    //Kochi is reachable from Multan with one stopover (e.g. Dubai)
    REQUIRE(iddfs.runIDDFS(2214, 3136, 2));
```

## Final Thoughts

This project provided us insight into a very important and upcoming field, data science. Cleaning the raw data is an essential part of data science and these skills would be quite valuable in our future endeavors. Furthermore, this project provided us cognizance of how algorithms and graphs are used in real world applications as most of the work we had done till now was theoretical. Overall all of our algorithms worked in the manner we intended them too. I believe we could have improved the runtime efficiency for DFS, but overall it worked within the limits we had proscribed. Furthermore, we could have also implemented an adjacency list rather than an adjacency matrix to store our graph; however, we got around that by creating an unordered map of the neighbors. One thing we can look towards adding in the future is figuring out the shortest possible flight plan from one airport to another. This can be done using a combination of Djikstra and IDDFS or finding another suitable algorithm.
