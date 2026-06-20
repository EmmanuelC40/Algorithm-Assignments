#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIXLENGTH 500
#define PUZZLE_SIZE 15
#define ROWS 3
#define COLS 5
#define MAX_STATES 4000000
#define QUEUE_SIZE 4000000

/* Checks if puzzle is solved */
int solved(char *a)
{
    int i;
    for (i = 0; i < 4; i++)
        if (a[i] != 'a')
            return 0;
    for (i = 5; i < 10; i++)
        if (a[i] != 'b')
            return 0;
    for (i = 10; i < 15; i++)
        if (a[i] != 'c')
            return 0;
    return 1;
}

/* print the puzzle state */
void printpuzzle(char *a)
{
    int i, j;
    printf("\n");
    for (i = 0; i < 3; i++)
    {
        printf("\t");
        for (j = 0; j < 5; j++)
            printf("%c", a[5 * i + j]);
        printf("\n");
    }
}

/* validate puzzle state */
int validpuzzle(char *a)
{
    int i;
    for (i = 0; i < 15; i++)
        if (a[i] != 'a' && a[i] != 'b' && a[i] != 'c' && a[i] != 'X')
            return 0;
    return 1;
}

/* movement functions */
void left(char *a)
{
    int i, j, gapx, gapy;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            if (a[5 * i + j] == 'X')
            {
                gapx = j;
                gapy = i;
            }
    if (gapx == 0)
        return;
    a[5 * gapy + gapx] = a[5 * gapy + gapx - 1];
    a[5 * gapy + gapx - 1] = 'X';
}

void right(char *a)
{
    int i, j, gapx, gapy;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            if (a[5 * i + j] == 'X')
            {
                gapx = j;
                gapy = i;
            }
    if (gapx == 4)
        return;
    a[5 * gapy + gapx] = a[5 * gapy + gapx + 1];
    a[5 * gapy + gapx + 1] = 'X';
}

void up(char *a)
{
    int i, j, gapx, gapy;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            if (a[5 * i + j] == 'X')
            {
                gapx = j;
                gapy = i;
            }
    if (gapy == 0)
        return;
    a[5 * gapy + gapx] = a[5 * gapy + gapx - 5];
    a[5 * gapy + gapx - 5] = 'X';
}

void down(char *a)
{
    int i, j, gapx, gapy;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 5; j++)
            if (a[5 * i + j] == 'X')
            {
                gapx = j;
                gapy = i;
            }
    if (gapy == 2)
        return;
    a[5 * gapy + gapx] = a[5 * gapy + gapx + 5];
    a[5 * gapy + gapx + 5] = 'X';
}

typedef struct
{
    char state[PUZZLE_SIZE + 1];
    int depth;
    int parent;
    char move;
} Node;

/* Encode puzzle state as integer (2 bits per tile) */
unsigned long encode_state(const char *s)
{
    unsigned long code = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        unsigned long val = (s[i] == 'a') ? 0 : (s[i] == 'b') ? 1
                                        : (s[i] == 'c')       ? 2
                                                              : 3;
        code = (code << 2) | val;
    }
    return code;
}

/* Hashing for encoded states */
unsigned long hash_state(unsigned long code)
{
    code ^= (code >> 21);
    code ^= (code << 17);
    code ^= (code >> 4);
    return code % MAX_STATES;
}

/* Insert into visited table, returns 1 if new, 0 if already seen */
int visited_insert(unsigned long *visited, unsigned long code)
{
    unsigned long h = hash_state(code);
    while (visited[h])
    {
        if (visited[h] == code)
            return 0;
        h = (h + 1) % MAX_STATES;
    }
    visited[h] = code;
    return 1;
}

/* BFS solver to find the shortest path to the solved puzzle */
int bfs_solve(const char *start)
{
    Node *queue = malloc(sizeof(Node) * QUEUE_SIZE);
    unsigned long *visited = calloc(MAX_STATES, sizeof(unsigned long));
    if (!queue || !visited)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }

    int front = 0, rear = 0;

    /* Initialize the start state */
    Node root;
    strcpy(root.state, start);
    root.depth = 0;
    root.parent = -1;
    root.move = '\0';
    queue[rear++] = root;

    visited_insert(visited, encode_state(start));

    const char moves[4] = {'L', 'R', 'U', 'D'};
    int explored = 0;

    while (front < rear)
    {
        Node curr = queue[front];
        int curr_idx = front++;
        explored++;

        if (solved(curr.state))
        {
            printf("\nPuzzle solved after exploring %d states!\n", explored);
            printf("\nShortest path length: %d moves\n", curr.depth);

            /* Reconstruct path */
            if (curr.depth > 0)
            {
                char *path = malloc(curr.depth + 1);
                int idx = curr.depth - 1;
                int trace_idx = curr_idx;
                while (queue[trace_idx].parent != -1)
                {
                    path[idx--] = queue[trace_idx].move;
                    trace_idx = queue[trace_idx].parent;
                }
                path[curr.depth] = '\0';
                printf("\nPath to solution: %s\n", path);
                free(path);
            }
            free(queue);
            free(visited);
            return curr.depth;
        }

        /* Try all possible moves */
        for (int m = 0; m < 4; m++)
        {
            Node next = curr;

            switch (moves[m])
            {
            case 'L':
                left(next.state);
                break;
            case 'R':
                right(next.state);
                break;
            case 'U':
                up(next.state);
                break;
            case 'D':
                down(next.state);
                break;
            }

            /* If the move did not change state, skip it */
            if (strcmp(next.state, curr.state) == 0)
                continue;

            unsigned long code = encode_state(next.state);
            if (visited_insert(visited, code))
            {
                next.depth = curr.depth + 1;
                next.parent = curr_idx;
                next.move = moves[m];
                queue[rear++] = next;
            }
        }
    }

    printf("\nNo solution found.\n");
    free(queue);
    free(visited);
    return -1;
}

/* Main Program */
int main()
{
    char b[16] = "aaaaXbbbbbccccc";
    int i, k;
    printf("\nCreated Puzzle:\n");
    printpuzzle(b);

    printf("\nNow mixing up...\n");
    srand(time(NULL));
    for (i = 0; i < MIXLENGTH; i++)
    {
        k = rand() % 4;
        if (k == 0)
            left(b);
        else if (k == 1)
            down(b);
        else if (k == 2)
            right(b);
        else
            up(b);

        if (validpuzzle(b) == 0)
        {
            printf("ERROR\n");
            printpuzzle(b);
            printf("\n %dth move; last move was %d\n", i, k);
            exit(0);
        }
    }

    printf("\nMixed Puzzle:\n");
    printpuzzle(b);
    printf("\nNow solving with BFS...\n");

    int steps = bfs_solve(b);
    if (steps >= 0)
        printf("\nSolved in %d moves!\n", steps);
    else
        printf("\nCould not find a solution.\n");

    return 0;
}
