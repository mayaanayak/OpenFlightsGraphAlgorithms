# Final Project Proposal

## Leading Question
If a traveler wants to fly into an airport B, then they would want to fly out of an airport A such that airport B is reachable from airport A. We will determine if airport B is reachable from airport A by implementing the union-find algorithm not covered in class. We also want to determine the shortest path between airports A and B, for which we will use Dijkstra's algorithm covered in class. We will also use a depth-first search (DFS) traversal to determine if, given three airports A, B, and C, it is possible to visit one or more of A, B, or C more than once.

## Dataset Acquisition and Processing
We will employ the provided OpenFlights data (https://openflights.org/data.html) in completing this project. This data is in a comma-separated format, and it is composed of 14,110 records. We will be using a subset of this dataset (airports only).

We will parse our comma-separated (CSV) data using the fstream library (delimiting with commas), converting the CSV into a malleable 2D vector format. The dataset denotes missing entries with a null character (“\N”); the dataset contains 3,354 such entries. These null characters do not occur in columns relevant to our analysis (airport name, airport ID, latitude, longitude), so they are not a concern. We will identify outliers with the IQR method, and we will drop egregious outliers from the dataset.

Loading the data has a storage cost of O(n), where n is the number of input nodes (each node represents an airport). We will use a two-dimensional std::vector to store this. In finding the shortest path between two airports, we must store the distances between each path. This will also have storage cost O(m) and will be accomplished using a two-dimensional std::vector. In finding the fewest number of flights needed to travel from airport A to airport B, we will use a queue, which has storage cost O(n), where n is the number of input nodes. In finding the shortest path between two airports, we will use a min-heap to find the node with the minimum distance from a given node, which has storage cost O(n), where n is the number of input nodes.

## Graph Algorithms
We will consider a spherical map in defining the distance between two coordinates. We will use the haversine formula (in place of the traditional distance formula) to find the great-circle distance between points.

To utilize our algorithms, we will first convert our data into an adjacency matrix in order to form our graph. The adjacency matrix will be a two dimensional vector in which the index of the rows and columns will represent our airports while the fields will not only tell us whether the airports are connected by an edge but, as the graph will be weighted, they will also tell the distance between each connected airport. We are utilizing adjacency matrix because firstly it is easier to implement especially with regards to our two dimensional vector dataset. Adjacency matrices also allows quick deletion of edges (constant time) which will improve our time complexity in our Boruvka's algorithm.

We will use Depth First Search (DFS) traversal to first determine if, given three airports A, B, and C, it is possible to visit one or more of A, B, or C more than once. The traversal will take our starting position, the other input airports, and the adjacency matrix as inputs. It will then return true or false depending on whether a cycle exists between the given airports. This will be done by detecting whether a cycle exists between the given nodes. Our desired time complexity will be O(V+E), where V is the number of vertices and E is the number of edges in the graph. Our desired space complexity will be O(V).

We will use a union-find algorithm to find whether a path exists between two airports. The algorithm will take our adjacency matrix, a starting airport/node, and a destination airport/node as its inputs. The program will then output the shortest possible path you can take between two nodes and a value which represents the total distance. The space complexity of our algorithm will be O(V + E) where V is the number of vertices/airports and E is the number of edges in the graph, while its time complexity would be O(E(log(V)) if we optimize it.

We will use Dijkstra's algorithm to find the fewest number of flights needed to travel between two airports. Our input will be our adjacency matrix, the source airport, and the target airport. It will return a list output indicating this shortest path. Our desired time complexity is O(V + E log V) and our desired space complexity is O(V), where E is the number of edges in the graph and V is the number of vertices/airports.
## Timeline 

Team Contract - 11th March

Team Proposal - 24th March 

Finalizing project structure and algorithms - 26th March 

Data acquisition, data processing - 7th April 

Implement algorithm covered in class - 12th April 

Implement graph traversal (will take up to ten days) - 22th April 

Implement algorithm not covered in class - 28th April 

## Mid Project Check-in - 15th April 

Write test cases for each of the graph traversal and the two algorithms we will be implementing - 3rd May

Final compilation & Final presentation - 4th May

Written report - 5th May
