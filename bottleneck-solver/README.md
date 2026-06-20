# 3. Bottleneck Path Solver (C)

## Overview
This program computes the **minimum bottleneck path** between two points in a 2D plane.

Given a set of 2D points, the goal is to find a path from the **first point** to the **second point** such that the **maximum Euclidean distance between any two consecutive points along the path is minimized**.

The solution combines:

* **Distance Caching** to minimize expensive floating-point math.
* **Binary Search** on sorted edge distances to find the optimal threshold.
* **Depth-First Search (DFS)** for $O(1)$ lookup feasibility testing.
* **Breadth-First Search (BFS)** to reconstruct the shortest hop path.

## Problem Description

Given a set of points in 2D space:

* Each point represents a node.
* A fully connected graph is assumed initially (an edge exists between every pair of nodes).
* The edge weight is the Euclidean distance between the points.
* The **bottleneck distance** of a path is the maximum edge weight along that path.

### Objective

Find a path from point `0` to point `1` such that the bottleneck distance is minimized.

## Input & Output Format

### Input Format 

The program reads points from a text file specified via the command line. Each line must contain a point in the following format:

```
(x, y)
```

**Example (`points.txt`):**
```
(0,0)
(25,20)
(5,0)
(10,0)
(15,0)
(20,0)
(25,5)
(25,10)
(25,15)
(0,5)
(5,5)
(10,5)
(15,5)
(20,5)
(0,10)
(5,10)
(10,10)
(15,10)
(20,10)
(0,15)
(5,15)
(10,15)
(15,15)
(20,15)
(0,20)
(5,20)
(10,20)
(15,20)
(20,20)
(25,0)
```

### Output Format

The program outputs the sequence of points along the minimum bottleneck path, followed by the exact bottleneck distance.

**Example Output:**
```
(0,0)
(5,0)
(10,0)
(15,0)
(20,0)
(20,5)
(25,5)
(25,10)
(25,15)
(25,20)

Bottleneck Distance: 5.000000
```

## Algorithm

### High-Level Approach
1. **Precompute & Cache:** Calculate all $O(N^2)$ pairwise Euclidean distances and store them in a 2D matrix.
2. **Sort:** Copy and sort the unique edge distances using a custom quicksort algorithm.
3. **Binary Search:** Conduct a binary search over the sorted distances to find the smallest distance $D$ where a path from point 0 to point 1 exists using only edges of length $\le D$.
4. **Build Graph:** Construct the final adjacency matrix using the optimized threshold $D$.
5. **Reconstruct Path:** Perform a BFS from point 0 to point 1 to find the shortest hop sequence and backtrack via parent pointers.

### Feasibility Check (DFS)

For a candidate distance threshold $D$:

* Run a recursive DFS starting from node 0.
* Edge traversals check the precomputed distance matrix in $O(1)$ time.
* Edges greater than $D$ are ignored.
* If node 1 is reached, the bottleneck threshold $D$ is marked feasible.

### Path Reconstruction (BFS)

Once the optimal bottleneck distance $D$ is determined:

* Build an adjacency matrix representing the valid unweighted graph.
* Perform BFS from node `0` to node `1`.
* Track parent nodes during the traversal to backtrack and print the final path from start to finish.

## Implementation Details

### Key Data Structures

```C
typedef struct {
    double x, y;
} Point;
```

* **Points Array:** Stored in an array of a fixed maximum size (capped at 500).
* **Distance Matrix:** A 2D array (`distMatrix[MAXN][MAXN]`) caches all pairwise distances once at startup, eliminating redundant `sqrt()` calls during graph traversals.
* **Adjacency Matrix:** A 2D bit-matrix representing structural connectivity after the bottleneck threshold is finalized.

### Sorting

* A custom **quicksort** implementation is used to sort all pairwise distances.
* This avoids reliance on standard library (`qsort`) functions.

## File Description
| File | Description |
| --- | --- |
| bottleneck.c | Bottleneck path solver implementation |
| points.txt | Sample input file containing 2D points |


## Build and Run

### Prerequisites
You will need a C compiler (like `gcc`) installed on your system. Standard C libraries (math.h requires explicit linking)

### Compilation
Compile the program using the following terminal command:

```
gcc bottleneck.c -o bottleneck -lm
```

*(Note: The -lm flag is required to link the math library for sqrt.)*

### Execution

Run the program by passing the input file as an argument:

```
./bottleneck points.txt
```

## Time and Space Complexity

Let `N` be the number of points.

| Operation | Complexity | Description|
| --- | --- | --- |
| Distance Matrix Build | $O(N^2)$ | Computes all pairwise distances and caches them once. | 
| Sorting Distances | $O(N^2 \log N)$ | Sorts unique distances for the binary search. |
| Binary Search Loop | $O(\log N)$ | Bounds the optimal bottleneck value. | 
| DFS Feasibility Check | $O(N^2)$ | Runs per binary search step using $O(1)$ matrix lookups. | 
| BFS Path Reconstruction | $O(N^2)$ | Traverses final adjacency matrix to trace the path. | 

* **Overall Time Complexity:** $O(N^2 \log N)$ (dominated by sorting the edge distances).
* **Overall Space Complexity:** $O(N^2)$ due to the distMatrix cache and adj matrix allocation. For $N = 500$, memory usage remains exceptionally low ($\approx 2 \text{ MB}$).

## Notes and Assumptions

* The maximum number of points is capped at **500**.
* Input file must follow the exact `(x, y)` format.
* Points are indexed in the order they appear in the file.
* **Floating-Point Support:** Coordinates are printed using `%g` formatting, which accurately scales to support both integer and decimal-valued inputs without truncation.
* **Error Handling:** The program explicitly validates graph connectivity. If point 0 and point 1 are completely disconnected, the program outputs a clean error message and exits safely.

## Author

**Emmanuel Cano**

Assignment 3 – Bottleneck Path Solver

Implemented in C
