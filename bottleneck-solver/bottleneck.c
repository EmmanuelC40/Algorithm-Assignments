#include <stdio.h>
#include <math.h>

#define MAXN 500

typedef struct {
    double x, y;
} Point;

Point pts[MAXN];
double distList[MAXN * MAXN];
double distMatrix[MAXN][MAXN]; // Caches distances to avoid repeating sqrt()
int N = 0;
int adj[MAXN][MAXN];   
int visited[MAXN];
int parent[MAXN];

/* Euclidean distance */
double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

/* Swap helper for quicksort */
void swap(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

/* Simple quicksort function */
void qsort_double(double arr[], int left, int right) {
    if (left >= right) return;
    double pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++; 
            j--;
        }
    }

    if (left < j) qsort_double(arr, left, j);
    if (i < right) qsort_double(arr, i, right);
}

/* DFS used during binary search */
int dfs(int u, int target, double maxDist) {
    if (u == target) return 1;
    visited[u] = 1;

    for (int v = 0; v < N; v++) {
        if (!visited[v] && distMatrix[u][v] <= maxDist) {
            if (dfs(v, target, maxDist)) return 1;
        }
    }
    return 0;
}

/* BFS used after determining the final bottleneck distance */
int bfs_path(int start, int target) {
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    int queue[MAXN];
    int front = 0, back = 0;

    visited[start] = 1;
    queue[back++] = start;

    while (front < back) {
        int u = queue[front++];

        if (u == target) return 1;

        for (int v = 0; v < N; v++) {
            if (!visited[v] && adj[u][v]) {
                visited[v] = 1;
                parent[v] = u;
                queue[back++] = v;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    /* Read all points from file */
    while (fscanf(fp, " ( %lf, %lf ) ", &pts[N].x, &pts[N].y) == 2) {
        N++;
        if (N >= MAXN) break;
    }
    fclose(fp);

    if (N < 2) {
        printf("Need at least 2 points.\n");
        return 1;
    }

    /* Build distance matrix and list of pairwise distances */
    int Dcount = 0;
    for (int i = 0; i < N; i++) {
        distMatrix[i][i] = 0.0; 
        for (int j = i + 1; j < N; j++) {
            double d = dist(pts[i], pts[j]);
            distMatrix[i][j] = d;
            distMatrix[j][i] = d;
            distList[Dcount++] = d;
        }
    }

    /* Sort distances for binary search */
    qsort_double(distList, 0, Dcount - 1);

    /* Binary search to find minimum distance threshold */
    int lo = 0, hi = Dcount - 1, best = hi;
    int path_exists = 0;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        double limit = distList[mid];

        for (int i = 0; i < N; i++) visited[i] = 0;

        /* DFS checks whether threshold 'limit' connects 0 to 1 */
        if (dfs(0, 1, limit)) {
            best = mid;
            path_exists = 1;
            hi = mid - 1;   /* Try to find a smaller valid bottleneck */
        } else {
            lo = mid + 1;
        }
    }

    /* Handle the edge case where node 0 and 1 are completely physically disconnected */
    if (!path_exists) {
        printf("No path exists between point 0 and point 1.\n");
        return 1;
    }

    double bottleneck = distList[best];

    /* Build final adjacency matrix with chosen bottleneck distance */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adj[i][j] = (distMatrix[i][j] <= bottleneck) ? 1 : 0;
        }
    }

    /* BFS to retrieve an actual minimum-edge path from 0 to 1 */
    bfs_path(0, 1);

    /* Reconstruct path in reverse */
    int path[MAXN];
    int length = 0;
    int cur = 1;

    while (cur != -1) {
        path[length++] = cur;
        cur = parent[cur];
    }

    /* Fixed printing format using %g to accurately support floating-point coordinates */
    for (int i = length - 1; i >= 0; i--) {
        int p = path[i];
        printf("(%g,%g)\n", pts[p].x, pts[p].y);
    }

    printf("\nBottleneck Distance: %.6lf\n", bottleneck);

    return 0;
}