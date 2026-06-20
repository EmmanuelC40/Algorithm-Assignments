#include <stdio.h>
#include <math.h>

#define MAXPTS 50

typedef struct {
    int x, y;
} Point;

/* Euclidean distance */
double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

/* Parse line of form "(123,45)" */
int parse_point(const char *s, Point *p) {
    return sscanf(s, " ( %d , %d ) ", &p->x, &p->y );
}

/* Strategy 1: each request served by closest server */
double closest_strategy(Point req[], int n, char sequence[]) {
    Point r = {0,0}, b = {300,300};
    double red_total = 0, blue_total = 0;

    for (int i = 0; i < n; i++) {
        double dr = dist(r, req[i]);
        double db = dist(b, req[i]);

        if (dr <= db) {
            sequence[i] = 'r';
            red_total += dr;
            r = req[i];
        } else {
            sequence[i] = 'b';
            blue_total += db;
            b = req[i];
        }
    }
    sequence[n] = '\0';
    return red_total + blue_total;
}

/* Strategy 2: serve with server that has traveled least total distance so far */
double least_traveled_strategy(Point req[], int n, char sequence[]) {
    Point r = {0,0}, b = {300,300};
    double red_total = 0, blue_total = 0;

    for (int i = 0; i < n; i++) {
        double dr = dist(r, req[i]);
        double db = dist(b, req[i]);

        /* hypothetical totals */
        double r_new = red_total + dr;
        double b_new = blue_total + db;

        if (r_new <= b_new) {
            sequence[i] = 'r';
            red_total = r_new;
            r = req[i];
        } else {
            sequence[i] = 'b';
            blue_total = b_new;
            b = req[i];
        }
    }
    sequence[n] = '\0';
    return red_total + blue_total;
}

/* Strategy 3: Optimal via Dynamic Programming (DP)
   DP[i][j] = minimal cost if red at i, blue at j, next request is k = max(i,j)+1.
*/
double min(double a, double b) { return a < b ? a : b; }

double optimal_strategy(Point req[], int n, char sequence[]) {
    static double dp[MAXPTS+1][MAXPTS+1];
    static char choice[MAXPTS+1][MAXPTS+1];
    static int previ[MAXPTS+1][MAXPTS+1];
    static int prevj[MAXPTS+1][MAXPTS+1];

    /* Initialize DP table */
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 1e18;

    dp[0][0] = 0;

    /* Fill DP */
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {

            int k = (i > j ? i : j) + 1;
            if (k > n) continue;

            Point r = (i == 0) ? (Point){0,0} : req[i-1];
            Point b = (j == 0) ? (Point){300,300} : req[j-1];

            /* Red serves request k */
            double cost_r = dp[i][j] + dist(r, req[k-1]);
            if (cost_r < dp[k][j]) {
                dp[k][j] = cost_r;
                choice[k][j] = 'r';
                previ[k][j]  = i;
                prevj[k][j]  = j;
            }

            /* Blue serves request k */
            double cost_b = dp[i][j] + dist(b, req[k-1]);
            if (cost_b < dp[i][k]) {
                dp[i][k] = cost_b;
                choice[i][k] = 'b';
                previ[i][k]  = i;
                prevj[i][k]  = j;
            }
        }
    }

    /* Find best ending cell */
    double best = 1e18;
    int bi = 0, bj = 0;

    for (int i = 0; i <= n; i++) {
        if (dp[i][n] < best) { best = dp[i][n]; bi = i; bj = n; }
        if (dp[n][i] < best) { best = dp[n][i]; bi = n; bj = i; }
    }

    /* Backtrack */
    int k = n;
    while (k > 0) {
        char c = choice[bi][bj];
        sequence[k-1] = c;

        int pi = previ[bi][bj];
        int pj = prevj[bi][bj];

        bi = pi;
        bj = pj;
        k--;
    }

    sequence[n] = '\0';
    return best;
}


/* MAIN PROGRAM */

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

    Point req[MAXPTS];
    char line[100];
    int n = 0;

    while (fgets(line, sizeof(line), fp) && n < MAXPTS) {
        if (parse_point(line, &req[n])) n++;
    }
    fclose(fp);

    char seq1[MAXPTS+1], seq2[MAXPTS+1], seq3[MAXPTS+1];

    double d1 = closest_strategy(req, n, seq1);
    double d2 = least_traveled_strategy(req, n, seq2);
    double d3 = optimal_strategy(req, n, seq3);

    printf("1) Closest server:    %s  Total distance = %.3f\n", seq1, d1);
    printf("2) Least traveled:    %s  Total distance = %.3f\n", seq2, d2);
    printf("3) Optimal sequence:  %s  Total distance = %.3f\n", seq3, d3);

    return 0;
}