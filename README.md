# Algorithm Assignments in C

## Overview
This repository contains a collection of algorithm assignments implemented in **C**, developed as part of coursework focusing on algorithm design, analysis, and problem-solving techniques.

Each assignment is self-contained and demonstrates a different class of algorithms, ranging from sorting and graph traversal to optimization using dynamic programming.

The repository is organized so that each assignment:
* Lives in its own directory
* Includes a single C source file
* Includes a dedicated README with detailed explanations
* Uses optional `.txt` input files where required

## Repository Structure

```
algorithms/
|
├── bottleneck-solver/
│   ├── README.md
│   ├── bottleneck.c
│   └── points.txt
|
├── puzzle-solver-bfs/
│   ├── README.md
│   └── puzzle_solver_bfs.c
|
└── server-routes/
|   ├── README.md
|   ├── requests.txt
|   └── server_routes.c
|
├── word-sort/
|   ├── README.md
|   └── word_sort.c
|
└── README.md                # Main Menu
```

## Assignments Summary

### 1. Word Sort

**Techniques:** Sorting, Divide and Conquer

**Algorithm:** Merge Sort

Sorts words in a space-separated string into lexicographic order using a pointer-based merge sort implementation.

Emphasizes efficient memory usage and string manipulation in C.


**[📁 word-sort/](https://github.com/EmmanuelC40/Algorithm-Assignments/tree/958accab6855be7877e3194a22f0ec24367eb429/word-sort)**

---
### 2. Puzzle Solver (BFS)

**Techniques:** Graph Search, State Space Exploration

**Algorithm:** Breadth-First Search

Solves a 3×5 sliding puzzle using BFS to guarantee the shortest solution path.

Uses state encoding and hashing to efficiently track visited configurations.

**[📁 puzzle-solver-bfs/](https://github.com/EmmanuelC40/Algorithm-Assignments/tree/958accab6855be7877e3194a22f0ec24367eb429/puzzle-solver-bfs)**

---
### 3. Bottleneck Path Solver
**Techniques:** Graph Algorithms, Binary Search

**Algorithms:** DFS, BFS

Finds a minimum bottleneck path between two points in a fully connected geometric graph.

Uses binary search over sorted edge weights and graph traversal for feasibility testing.

**[📁 bottleneck-solver/](https://github.com/EmmanuelC40/Algorithm-Assignments/tree/958accab6855be7877e3194a22f0ec24367eb429/bottleneck-solver)**

---
### 4. Server Routing Strategies

**Techniques:** Greedy Algorithms, Dynamic Programming

**Algorithms:** Greedy Heuristics, DP Optimization

Compares two greedy strategies against an optimal dynamic programming solution for assigning service requests to two mobile servers.

Demonstrates tradeoffs between efficiency and optimality.

**[📁 server-routes/](https://github.com/EmmanuelC40/Algorithm-Assignments/tree/958accab6855be7877e3194a22f0ec24367eb429/server-routes)**

---
## Compilation

All programs are written in standard C and can be compiled using `gcc`.

Examples:

```
gcc word_sort.c -o word_sort
gcc puzzle__solver_bfs.c -o puzzle_solver_bfs
gcc bottleneck.c -o bottleneck -lm
gcc server_routes.c -o server_routes -lm
```

(`-lm` is required for programs using the math library.)

## Running the Programs

To run the assignments:

```
./word_sort
./puzzle_solver_bfs
```

Some assignments require input files:

```
./bottleneck test.txt
./server_routes requests.txt
```

Each assignment directory contains a README with exact usage instructions.

## Learning Objectives Demonstrated
* Divide-and-conquer sorting
* Graph traversal (BFS and DFS)
* State encoding and hashing
* Binary search over solution space
* Greedy algorithm design
* Dynamic programming with backtracking
* Time and space complexity analysis
* Low-level memory management in C

## Author

**Emmanuel Cano**

Algorithm Assignments

Implemented in C
