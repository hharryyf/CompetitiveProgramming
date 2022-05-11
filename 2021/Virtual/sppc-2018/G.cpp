#include <bits/stdc++.h>
#define MAX_SIZE 200111
using namespace std;

int parent[MAX_SIZE][18], depth[MAX_SIZE], N, Q;
vector<int> g[MAX_SIZE];
char tp[MAX_SIZE];

void dfs(int v, int d=1) {
    depth[v] = d;
    for (auto nv : g[v]) {
        dfs(nv, d + 1);
    }
}

void build() {
    int i, j;
    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 1; j < 18; ++j) {
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }
}

char op[3];

int main() {
    int i, ans = 0;
    scanf("%d%d", &N, &Q);
    for (i = 2; i <= N + 1; ++i) {
        scanf("%s%d", op, &parent[i][0]);
        g[parent[i][0]].push_back(i);
        tp[i] = op[0];
    }

    build();
    dfs(1);
    while (Q-- > 0) {
        int u, v;
        scanf("%d%d", &u, &v);
        int oru = u, orv = v;
        if (depth[u] < depth[v]) swap(u, v);
        for (i = 17; i >= 0; --i) {
            if (depth[u] >= (1 << i) + depth[v]) u = parent[u][i];
        }

        if (u == v) {
            if (depth[oru] < depth[orv]) swap(oru, orv);
            int d = depth[oru] - depth[orv] - 1;
            for (i = 17; i >= 0; --i) {
                if (d - (1 << i) >= 0) {
                    oru = parent[oru][i];
                    d = d - (1 << i);
                }
            }
            if (tp[oru] == 'L') ++ans;
        } else {
            for (i = 17; i >= 0; --i) {
                if (parent[u][i] != parent[v][i]) {
                    u = parent[u][i], v = parent[v][i];
                }
            }
            if (tp[u] == 'L' && tp[v] == 'L') ++ans;
            if (tp[u] == 'P' && tp[v] == 'L' && v < u) ++ans;
            if (tp[u] == 'L' && tp[v] == 'P' && u < v) ++ans; 
        }
    }

    printf("%d\n", ans);
    return 0;
}