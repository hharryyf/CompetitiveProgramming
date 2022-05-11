#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

const double inf = 1e8;
double dist[MAX_SIZE][MAX_SIZE];
int sgn(double x) {
    if (fabs(x) <= 1e-9) return 0;
    if (x > 0) return 1;
    return -1;
}

int N, K;

struct umbrella {
    int x, y, r;
};

umbrella ub[MAX_SIZE];

double sqr(int x) {
    return 1.0 * x * x;
}

double getdist(int i1, int i2) {
    double ds = sqrt(sqr(ub[i1].x - ub[i2].x) + sqr(ub[i1].y - ub[i2].y)) - ub[i1].r - ub[i2].r;
    //cout << "get " << i1 << " " << i2 << " = " << ds << endl;
    if (sgn(ds - K) <= 0) return max(ds, 0.0);
    return inf;
}

int main() {
    int i, j, k;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 0; j < MAX_SIZE; ++j) {
            if (i != j) dist[i][j] = inf;
        }
    }

    scanf("%d%d", &N, &K);
    scanf("%d%d", &ub[N + 1].x, &ub[N + 1].y);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d%d", &ub[i].x, &ub[i].y, &ub[i].r);
    }

    for (i = 0 ; i <= N + 1; ++i) {
        for (j = 0 ; j <= N + 1; ++j) {
            if (i != j) {
                dist[i][j] = min(dist[i][j], getdist(i, j));
            }
        }
    }
    /*
    for (i = 0 ; i <= N + 1; ++i) {
        for (j = 0 ; j <= N + 1; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
*/
    for (k = 0 ; k < N + 1; ++k) {
        for (i = 0 ; i < N + 1; ++i) {        
            for (j = 0 ; j < N + 1; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }   
        }     
    }

    double ans = inf;
    for (i = 0; i < N + 1; ++i) {
        for (j = 0 ; j < N + 1; ++j) {
            if (sgn(getdist(i, N + 1) + getdist(j, N + 1) - K) <= 0) {
                ans = min(ans, dist[0][i] + dist[i][N + 1] + dist[N + 1][j] + dist[j][0]);
            }
        }
    }

    if (ans < inf) {
        printf("%.10lf\n", ans);
    } else {
        printf("-1\n");
    }
    return 0;
}