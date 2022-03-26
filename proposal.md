# Final Project Proposal

## Leading Question
We will use the openflights dataset to collect data of flight routes and airports to construct a directed, weighted graph which shall be used for the following purposes:
1) Find the shortest path between two given airports
2) Find the shortest path between two given airports with a layover

We shall be using the Depth First Search(DFS) algorithm to traverse the graph. In order to find the shortest path between two nodes, i.e. airports, we shall implement Dijkstra's algorithm along with the landmark path algorithm.

## Dataset Acquisition and Processing
We will employ the provided OpenFlights data (https://openflights.org/data.html) in completing this project. This data is in a comma-separated format, and it is composed of 14,110 records. We will be using a subset of this dataset (airports only).
We will parse our comma-separated (CSV) data using the fstream library (delimiting with commas), converting the CSV into a malleable 2D vector format. The dataset denotes missing entries with a null character (“\N”); the dataset contains 3,354 such entries. These null characters do not occur in columns relevant to our analysis (airport name, airport ID, latitude, longitude), so they are not a concern. We will identify outliers with the IQR method, and we will drop egregious outliers from the dataset.

Loading the data has a storage cost of O(n), where n is the number of input nodes (each node represents an airport). We will use a two-dimensional std::vector to store this. In finding the shortest path between two airports, must store the distances between each path. This will also have storage cost O(m) and will be accomplished using a two-dimensional std::vector. In finding the shortest path between two airports, we will use a min-heap to find the node with the minimum distance from a given node, which has storage cost O(n), where n is the number of input nodes.

## Graph Algorithms
In order to utilize our algorithms, we will first convert our data into an adjacency matrix in order to form our graph. The adjacency matrix will be a two dimensional vector in which the index of the rows and columns will represent our airports while the fields will not only tell us whether the airports are connected by an edge but, as the graph will be weighted, they will also tell the distance between each connected airport.

We shall utilize Depth First Search (DFS) traversal to first determine whether a path exists between our two desired airports. The traversal will take our starting position, desired position, and the adjacency matrix as inputs. It will then return a boolean output which will tell us whether a path exists or not. Our desired time complexity will be O(V+E), where V is the number of vertices and E is the number of edges in the graph. Our desired space complexity will be O(V).

We shall utilize Djikstra’s algorithm in order to find the shortest distance between two airports. The algorithm will take our adjacency matrix, a starting airport/node, and a destination airport/node as its inputs. The program will then output the shortest possible path you can take between two nodes and a value which represents the total distance. The time and space complexity of our algorithm will be O(V^2) where V is the number of vertices/airports. 

Finally we shall utilize the Landmark Path Algorithm to determine the shortest possible path between two airports/nodes, provided a third airport that we need to visit in between. Our input for the algorithm will be our adjacency matrix, our starting node/airport, our destination node/airport, and the node/airport we want to visit in between. The algorithm will then output the shortest possible path and provide a value which represents the total distance. The time and space complexity of our Landmark Path Algorithm should be comparable to the Djikstra’s algorithm.


## Timeline 

Team Contract - 11th March

Team Proposal - 24th March 

Finalizing project structure and algorithms - 26th March 

Data acquisition, data processing - 1st April 

Implement algorithms covered in class - 1st April 

Implement graph traversal (will take upto ten days) - 10th April 

Implement algorithms not covered in class - 10th April 

## Mid Project Check-in - 15th April 

Write test cases for each of the graph traversal and the two algorithms we will be implementing - 20th April 

Final compilation & Final presentation - 30th April 
Written report - 1 May




