### Grade

Incomplete (0%)

Must resubmit!

Please select another uncovered algorithm. No penalty after resubmission.

### Checklist

Leading question
- [x] Interesting question or expected result
- [x] How the dataset and algorithms will answer this

Dataset
- [x] Data format (CSV, columns)
- [x] Acquire (Openflights)
- [x] Process (`fstream` )
- [x] Store (2D vector)
- [x] Data correction for potential errors (null, IQR/egregious outlier)

Algorithm
- [x] One graph traversal (DFS)
  - [x] Input and output
  - [x] Run-time efficiency
- [x] One algorithm in class (Dijkstra's)
  - [x] Input and output
  - [x] Run-time efficiency
- [ ] One algorithm not in class (Landmark Path Algorithm?)
  - [ ] Input and output
  - [ ] Run-time efficiency

Timeline
- [x] Reasonable date on every major benchmark.

### Comments

Great job on the clear **dataset** explanation! I appreciate your considerations and efforts to clean the data (N/A and outliers) before the main analysis as well. 

The leading question can be improved by stating the main question/problem/motivation more explicitly. Although I could make a guess, it'd be useful if you can explain the following. Why do we need to find the shortest path? Why a layover?

The major concern on the **algorithm** section is that we do not allow Landmark path as an uncovered algorithm. If the landmark/layover is given, how would the Landmark Path Algorithm differ from running Dijkstra's twice (source --> layover, layover --> destination)? Other comments:
- Is there always a connection between any arbitrary pair of airports? How dense is your graph? Would it be more time/space efficient to store it with adjacency list instead of adjacency matrix?
- How do you define the distance between two coordinates? Would you consider a spherical or flat map? One edge case to consider: latitude-longitude (89.9999, 0.0) is very close to (89.9999, 180.0).
- As an improvement, perhaps we could run a *union find* algorithm (covered in class) to serve the goal: "determine whether a path exists between our two desired airports". We'd have O(|V| + |E|) preprocessing and O(1) on each query of two given airports.

Please feel free to contact me if you have any further question or need clarification. Keep up the great work!