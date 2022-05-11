#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;
typedef long long ll;
const ll inf = 1e14;

struct edge {
    int from, to;
    ll w;
};

int ans[MAX_SIZE << 3];
edge edg[MAX_SIZE * MAX_SIZE];
int n, m;
int tol = 0;
ll dist[MAX_SIZE];

bool bellman_ford() {
    dist[0] = 0;
    int i, j;
    for (i = 1; i <= n * 2; ++i) {
        dist[i] = inf;
    }

    for (i = 0; i < n * 2; ++i) {
        for (j = 1; j <= tol; ++j) {
            edge &e = edg[j];
            dist[e.to] = min(dist[e.from] + e.w, dist[e.to]);
        }
    }

    for (j = 1; j <= tol; ++j) {
        edge &e = edg[j];
        if (dist[e.to] > dist[e.from] + e.w) {
            return false;
        }
    }

    return true;
}

int row(int x) {
    return x * 2 - 1;
}

int col(int x) {
    return x * 2;
}

int main() {
    int i, r, c;
    ll g;
    scanf("%d%lld%d%d", &n, &g, &r, &c);
    for (i = 1; i <= r; ++i) {
        int to, from;
        ll s, t;
        scanf("%d%d%lld%lld", &to, &from, &s, &t);
        // here add edge for system of different constraints
        // we know that s <= dist[to] - dist[from] <= t
        // it is  dist[to] - dist[from] <= 2 and dist[from] - dist[to] <= -1
        edg[++tol] = edge{row(from), row(to), t};
        edg[++tol] = edge{row(to), row(from), -s};   
    }

    for (i = 1; i <= c; ++i) {
        int to, from;
        ll s, t;
        scanf("%d%d%lld%lld", &to, &from, &s, &t);
        // here add edge for system of different constraints
        // we know that s <= dist[to] - dist[from] <= t
        // it is  dist[to] - dist[from] <= t and dist[from] - dist[to] <= -s
        edg[++tol] = edge{col(from), col(to), t};
        edg[++tol] = edge{col(to), col(from), -s};   
    }

    for (i = 1; i <= n; ++i) {
        // dist[i] - dist[0] >= 1
        // dist[i] - dist[0] <= g
        edg[++tol] = edge{row(i), 0, -1};
        edg[++tol] = edge{col(i), 0, -1};
        edg[++tol] = edge{0, row(i), g};
        edg[++tol] = edge{0, col(i), g};
    }

    if (!bellman_ford()) {
        printf("-1\n");
        return 0;
    }

    for (i = 1; i <= n; ++i) {
        printf("%lld %lld\n", dist[row(i)], dist[col(i)]);
    }
    return 0;
}
