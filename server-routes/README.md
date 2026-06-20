# 4. Server Routing Strategies and Dynamic Programming (C)

## Overview

This program evaluates three different strategies for assigning a sequence of service requests to **two mobile servers** in order to minimize total travel distance.

The strategies include:
1. A greedy **closest-server** approach.
2. A greedy **least-traveled-so-far** approach.
3. An **optimal solution using dynamic programming.**

By comparing these methods, the assignment demonstrates the strengths and limitations of greedy heuristics versus optimal dynamic programming solutions.

## Problem Description

Two servers are initially located at fixed positions:

* **Red server:** `(0, 0)`
* **Blue server:** `(300, 300)`

A sequence of service requests arrives one at a time, each located at a point in 2D space.

Each request must be served by **either** the red or blue server, and the chosen server moves to that request’s location.

### Objective

Determine an assignment of requests to servers that minimizes the **total distance traveled** by both servers.

## Input & Output Format

### Input Format 

The program reads request locations from a **text file** provided on the command line. Each line of the file contains one request in the format:

```
(x, y)
```

**Example (`requests.txt`):**

```
(50,50)
(260,260)
(80,200)
(30,300)
(200,40)
(290,150)
(100,260)
(220,280)
(40,120)
(250,30)
```

### Output Format

The program outputs the server assignment sequence for each strategy along with its total distance traveled. Each character in the sequence represents the server used:

* `r` $\rightarrow$ red server
* `b` $\rightarrow$ blue server

**Example Output:**

```
1) Closest server:    rbrrbbrrrb  Total distance = 1331.816
2) Least traveled:    rbrbrrbbbr  Total distance = 1425.430
3) Optimal sequence:  rbbbrrbbbr  Total distance = 1290.880
```

## Strategies Implemented

### 1. Closest-Server Strategy (Greedy)

Each request is served by the server that is **currently closest** to the request location.

* **Advantages:** Simple, fast, and requires no memory of past decisions.
* **Disadvantages:** Can lead to suboptimal long-term behavior.

### 2. Least-Traveled-So-Far Strategy (Greedy)

Each request is served by the server whose **total distance traveled so far would be smaller** after serving the request.

* **Advantages:** Considers accumulated cost. Often improves upon the closest-server approach.
* **Disadvantages:** Still greedy and not globally optimal.

### 3. Optimal Strategy (Dynamic Programming)

This strategy computes the **absolute minimum possible total distance** using dynamic programming and backtracking.

#### **DP State Definition**

`dp[i][j]` = minimum cost when:
* The **Red server** is at the location of request `i` (or origin if `i == 0`).
* The **Blue server** is at the location of request `j` (or origin if `j == 0`).
* The next request to serve is strictly $k = \max(i, j) + 1$.

#### **Branching**

Each state transitions into two choices: Red moves to serve $k$, or Blue moves to serve $k$.

Parent pointers are stored to reconstruct the optimal assignment sequence.

* **Advantages:** Guaranteed optimal solution.
* **Disadvantages:** Higher time and space complexity ( $O(n^2)$ ).

## Implementation Details

### Key Data Structures

```C
typedef struct {
    int x, y;
} Point;
```

* Requests are parsed safely from the text file using `sscanf` and stored in a static array.
* DP tables store floating-point minimum costs, and helper tables store backtracking coordinates and server choices (`r`/`b`).
* Maximum number of requests is capped at 50

### Path Reconstruction

After filling the DP table, the program scans the boundaries where at least one server has processed the final request `n`. It selects the absolute minimum total distance, then uses parent pointers (`previ`, `prevj`) to backtrack through the decisions to reconstruct and print the optimal server string sequence.

## File Description

| File | Description |
| --- | --- |
| server_routes.c | Implementation containing all three routing strategies and file parsing. |
| requests.txt | Sample input file containing 2D coordinate service requests. |


## Build and Run

### Prerequisites

You will need a C compiler (like `gcc`) installed on your system. Standard C libraries (math.h requires explicit linking)

### Compilation
Compile the program using the following terminal command:

```
gcc server_routes.c -o server_routes -lm
```

*(Note: The -lm flag is required to link the math library for sqrt.)*

### Execution

Run the program by passing the input file as an argument:

```
./server_routes requests.txt
```

## Time and Space Complexity

Let `n` be the number of requests.

| Strategy | Time Complexity | Space Complexity |
| --- | --- | --- |
| Closest-server | $O(n)$ | $O(1)$ |
| Least-traveled | $O(n)$ | $O(1)$ |
| Dynamic programming | $O(n²)$ | $O(n²)$ |


## Notes and Assumptions

* Requests are processed in the order they appear in the input file
* **Input Size Limit:** The maximum number of input points is capped at `50 (MAXPTS)`. If an input file contains more than 50 requests, the program will gracefully truncate the input and only process the first 50.
* Coordinates are integers, and distances are computed as double-precision floating-point numbers using standard Euclidean distance.
* Greedy strategies are included for comparison purposes

## Author

**Emmanuel Cano**

Assignment 4 – Server Routing Strategies

Implemented in C with Dynamic Programming
