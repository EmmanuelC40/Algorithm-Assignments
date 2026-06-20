# 1. Word Sort (C)

## Overview

This program sorts words in a space-separated string into **lexicographic (alphabetical) order.** The implementation is written in **C** and uses **Merge Sort** to efficiently sort the words.

Rather than copying entire strings during the sorting phase, the program:

* Splits the input string into words in-place by manipulating pointers.
* Stores pointers to the start of each word.
* Sorts the array of pointers using merge sort.
* Reconstructs the sorted output back into the original buffer using a temporary buffer.

This approach demonstrates efficient memory management and pointer-based string manipulation in C.

## Problem Description
Given a mutable character array containing words separated by spaces, the goal is to reorder the words in lexicographic order while preserving:

* All characters in the original buffer
* A single space between words
* A trailing space at the end of the string

The sorting of word pointers is performed in-place, and a temporary $O(n)$ buffer is utilized at the end to safely reconstruct the final string without data corruption.

## Algorithm

### High-Level Steps

1. **Scan the input string** to determine its total character length.
2. **Split the string into words** by replacing spaces (`' '`) with null terminators (`'\0'`).
3. **Store ‘char * ’ pointers** to the start of each word in an array.
4. **Sort the word pointers** using Merge Sort
5. **Rebuild the string** in sorted order with spaces between words

### Why Merge Sort?
Merge sort was selected because it guarantees:
* **$O$($w$ log $w$) time complexity** in worst, average, and best cases.
* **Stable ordering** (preserves the relative order of identical words).
* **Efficient pointer manipulation** (only the pointers are swapped, while the actual characters remain stationary in memory during sorting).

## Implementation Details

* Words are compared lexicographically using a custom comparison function
* Sorting is done on an array of `char *` pointers
* Dynamic memory is allocated for:
    * The word pointer array.
    * An auxiliary array used during the merge step.
    * A temporary buffer used to reconstruct the sorted string.

*Note: All dynamically allocated memory is strictly freed before program termination.*

### Assumptions

* Words are separated by **exactly a single space.**
* The input string always ends with a **trailing space.**
* The input buffer is mutable

These assumptions match the test cases provided in `main()`.

## File Description

| File | Description |
| --- | --- |
| word_sort.c | Full implementation including test cases and helper functions |

## Build and Run

### Prerequisites
You will need a C compiler (like `gcc`) installed on your system.

### Compilation

Compile the program using the following terminal command:
```
gcc word_sort.c -o word_sort
```

### Execution

Run the program:

```
./word_sort
```

*Note: The program automatically executes three test cases. This version runs pre-defined test cases within main() and does not accept interactive user input.*

## Test Cases & Expected Output

### Test 1 – Small Input (Vegetables)
Input:
```
pea carrot bean cabbage mushroom artichoke lentil onion leek
```

Output:
```
artichoke bean cabbage carrot leek lentil mushroom onion pea
```

### Test 2 – Medium Input (Animals)
Input:
```
raccoon chipmunk deer opossum coyote skunk rabbit bear groundhog
```

Output:
```
bear chipmunk coyote deer groundhog opossum rabbit raccoon skunk
```

### Test 3 – Large Input

* Automatically generated dataset of 10,000 words to demonstrate correctness and performance scales.
* Output displays a verified random fragment after successful sorting.

## Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
| --- | --- | --- |
| Splitting Input | $O(n)$ | $O(w)$ for pointer array |
| Sorting Pointers | $O$($w$ log $w$) | $O(w)$ auxiliary array |
| Rebuilding String | $O(n)$ | $O(n)$ temporary buffer |

* $n$ = Total number of characters in the input string.
* $w$ = Total number of words in the input string.

## Author

**Emmanuel Cano**

Assignment 1 – Word Sort

Implemented in C using Merge Sort
