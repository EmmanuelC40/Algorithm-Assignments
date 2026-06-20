# 2. Puzzle Solver Using Breadth-First Search (C)

## Overview

This program solves a **3×5 sliding puzzle** using **Breadth-First Search (BFS)** to find the **shortest sequence of moves** from a scrambled configuration to the solved state.

The puzzle consists of:

* Tiles labeled `'a'`, `'b'`, and `'c'`.
* One empty space represented by `'X'`.

The solver explores the state space level-by-level, guaranteeing that the first solution found is optimal (minimum number of moves).

## Puzzle Description

### Board Layout & Goal State

The puzzle is represented as a 1D character array of length 15 (plus a null terminator), corresponding to a 3×5 grid. 

The puzzle is considered solved when tiles are sorted row-by-row, locking `X` at the end of the first row:

```
aaaaX
bbbbb
ccccc
```

Legal moves slide a neighboring tile into the empty space: Left (L), Right (R), Up (U), and Down (D).

## Algorithm

### Breadth-First Search (BFS)

The solver uses **BFS** to explore all reachable puzzle configurations:

1. Start from a randomly mixed puzzle state.
2. Enqueue the initial state.
3. Repeatedly:
    * Dequeue the next state.
    * Check if it is solved.
    * Generate all valid neighboring states.
    * Insert unseen states into the queue.
4. Stop when the solved configuration is reached.

Because BFS explores states in increasing depth order, the solution found is guaranteed to be the **shortest path.**

## State Representation & Memory Optimizations

### 30-Bit State Hashing

To optimize lookup times and drastically reduce memory consumption in the visited registry, each board state is encoded into a **30-bit integer** (`unsigned long`):
* `'a'` $\rightarrow$ `00`
* `'b'` $\rightarrow$ `01`
* `'c'` $\rightarrow$ `10`
* `'X'` $\rightarrow$ `11`

### Visited-State Tracking

* A large lookup table tracking up to 4,000,000 states ensures no configuration is evaluated twice, preventing infinite loops.
* **Open addressing with linear probing** handles hash collisions using a custom bit-shifted hash multiplier.

## Implementation Details

### Core Data Structure

```C
typedef struct {
    char state[PUZZLE_SIZE + 1]; // 1D array representation of the board
    int depth;      // Current number of moves from start
    int parent;     // Index of the parent node in the queue buffer
    char move;      // The move (L, R, U, D) that led to this state
} Node;
```

### Path Reconstruction

When the goal state is flagged, the program traces the `parent` indices backward through the queue allocation buffer, reversing the sequence to print the clean forward path string (e.g., `LURD...`).

## Random Puzzle Generation

Before solving:

* The puzzle starts in the solved state.
* It is scrambled using **500 random valid moves**.
* This guarantees the puzzle remains solvable.

## File Description

| File | Description |
| --- | --- |
| puzzle_solver_bfs.c | BFS-based puzzle solver with random mixing and solution reconstruction |

## Build and Run

### Prerequisites

You will need a C compiler (like `gcc`) installed on your system.

### Compilation

Compile the program using the following terminal command:

```
gcc puzzle_solver_bfs.c -o puzzle_solver_bfs
```

### Execution

Run the solver:

```
./puzzle_solver_bfs
```

The program will:
1. Display the initial puzzle.
2. Randomly mix it.
3. Solve it using BFS.
4. Print:
    * Number of explored states.
    * Shortest path length.
    * Sequence of moves to solve the puzzle.

## Output Example

```
Created Puzzle:
	
    aaaaX
	bbbbb
	ccccc

Now mixing up...

Mixed Puzzle:
	
    bXaab
	cabbc
	cccab

Now solving with BFS...

Puzzle solved after exploring 226817 states!

Shortest path length: 19 moves

Path to solution: DRRDLLLUURRRDRDLURU

Solved in 19 moves!
```

## Time and Space Complexity

| Aspect | Complexity | Description |
| --- | --- | --- |
| Time | $O(b^d)$ | Where $b$ is the effective branching factor and $d$ is the solution depth. |
| Space | $O(b^d)$ | Dominated by the 4,000,000 slot array buffers allocated for the BFS queue (~112 MB) and the visited hash table (~32 MB).| 

## Author

**Emmanuel Cano**

Assignment 2 – Puzzle Solver

Implemented in C using Breadth-First Search
