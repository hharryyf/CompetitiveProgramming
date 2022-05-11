#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

struct edge {
    int from, to, wt;
    bool select;
    bool operator < (edge other) const {
        return wt < other.wt;
    }
};

int a[MAX_SIZE][MAX_SIZE];
int N;
int f[MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
edge edg[MAX_SIZE * MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void dfs(int src, int v, int pre, int d=0) {
    dist[src][v] = d;
    for (auto np : g[v]) {
        int nv = np.first, w = np.second;
        if (nv != pre) {
            dfs(src, nv, v, d + w);
        }
    }
}

int main() {
    while (scanf("%d", &N) != EOF) {
        int i, j, k = 0;
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                scanf("%d", &a[i][j]);
                edg[k++] = {i, j, a[i][j], false};
            }
            g[i].clear();
            f[i] = i;
        }

        sort(edg, edg + k);
        for (i = 0; i < k; ++i) {
            if (find(edg[i].from) != find(edg[i].to)) {
                unionset(edg[i].from, edg[i].to);
                g[edg[i].from].emplace_back(edg[i].to, edg[i].wt);
                g[edg[i].to].emplace_back(edg[i].from, edg[i].wt);
                edg[i].select = true;
            }
        }

        for (i = 1; i <= N; ++i) {
            dfs(i, i, 0, 0);
        }
        
        bool hasedge = false;

        for (i = 0 ; i < k; ++i) {
            if (edg[i].wt != 0 && !edg[i].select) {
                if (edg[i].wt != dist[edg[i].from][edg[i].to]) {
                    edg[i].select = true;
                    hasedge = true;
                    break;
                }
            }
        }

        if (!hasedge) {
            for (i = 0 ; i < k; ++i) {
                if (edg[i].from != edg[i].to && !edg[i].select) {
                    edg[i].select = true;
                    break;
                }
            }
        }

        for (i = 0 ; i < k; ++i) {
            if (edg[i].select) {
                printf("%d %d %d\n", edg[i].from, edg[i].to, edg[i].wt);
            }
        }
        printf("\n");
    }
    return 0;
}