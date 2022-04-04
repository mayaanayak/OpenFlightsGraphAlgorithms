# Final Project Proposal

## Leading Question
If a traveler wants to fly into an airport B, then they would want to fly out of an airport A such that airport B is reachable from airport A. We will determine if airport B is reachable from airport A by implementing the union-find algorithm covered in class. Additionally, though they are unavoidable, most travelers dread layovers. Thus, we would like to determine the fewest number of flights necessary to travel from airport A to airport B (given that airport B is reachable from airport A) through a breadth-first search (BFS) traversal. While not wholly applicable to a practical scenario, we are also determining the shortest length path one could take to visit all of the airports in our dataset. To this end, we will implement Boruvka's algorithm. We will implement these algorithms and traversal by first constructing a directed, weighted graph.

## Dataset Acquisition and Processing
We will employ the provided OpenFlights data (https://openflights.org/data.html) in completing this project. This data is in a comma-separated format, and it is composed of 14,110 records. We will be using a subset of this dataset (airports only).

We will parse our comma-separated (CSV) data using the fstream library (delimiting with commas), converting the CSV into a malleable 2D vector format. The dataset denotes missing entries with a null character (“\N”); the dataset contains 3,354 such entries. These null characters do not occur in columns relevant to our analysis (airport name, airport ID, latitude, longitude), so they are not a concern. We will identify outliers with the IQR method, and we will drop egregious outliers from the dataset.

Loading the data has a storage cost of O(n), where n is the number of input nodes (each node represents an airport). We will use a two-dimensional std::vector to store this. In finding the shortest path between two airports, we must store the distances between each path. This will also have storage cost O(m) and will be accomplished using a two-dimensional std::vector. In finding the fewest number of flights needed to travel from airport A to airport B, we will use a queue, which has storage cost O(n), where n is the number of input nodes. 

In finding the shortest path between two airports, we will use a min-heap to find the node with the minimum distance from a given node, which has storage cost O(n), where n is the number of input nodes.

## Graph Algorithms
We will consider a spherical map in defining the distance between two coordinates. We will use the haversine formula (in place of the traditional distance formula) to find the great-circle distance between points.

In order to utilize our algorithms, we will first convert our data into an adjacency matrix in order to form our graph. The adjacency matrix will be a two dimensional vector in which the index of the rows and columns will represent our airports while the fields will not only tell us whether the airports are connected by an edge but, as the graph will be weighted, they will also tell the distance between each connected airport.

We shall utilize Breadth First Search (BFS) traversal to first determine the fewest number of flights need to travel between two airports. The traversal will take our starting position, desired position, and the adjacency matrix as inputs. It will then return a list output indicating the shortest path. Our desired time complexity will be O(V+E), where V is the number of vertices and E is the number of edges in the graph. Our desired space complexity will be O(V).

We will use a union-find algorithm to find the shortest distance between two airports. The algorithm will take our adjacency matrix, a starting airport/node, and a destination airport/node as its inputs. The program will then output the shortest possible path you can take between two nodes and a value which represents the total distance. The time and space complexity of our algorithm will be O(V^2) where V is the number of vertices/airports. 

Finally we shall utilize Boruvka's algorithm to create a minimum spanning tree with only the edges that are essential to keep the graph fully connected. Our input shall be the directed graph and shall begin by finding the minimum-weight edge incident to each vertex of the graph, and adding all of those edges to the forest. Then by repeating a similar process, it will reduce the number of trees within each connected component of the graph, to at most half of this former value, so after logarithmically many repetitions the process finishes. When it does, the set of edges it has added forms the minimum spanning forest. The minimum spanning forest, shall be our output, ie the shortest path that a passenger can take in order to visit all airports in our dataset. 

## Timeline 

Team Contract - 11th March

Team Proposal - 24th March 

Finalizing project structure and algorithms - 26th March 

Data acquisition, data processing - 7thst April 

Implement algorithms covered in class - 12th April 

Implement graph traversal (will take up to ten days) - 22th April 

Implement algorithms not covered in class - 28th April 

## Mid Project Check-in - 15th April 

Write test cases for each of the graph traversal and the two algorithms we will be implementing - 3rd May

Final compilation & Final presentation - 4th May

Written report - 5th May




