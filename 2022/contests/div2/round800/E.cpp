#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 200011

struct node {
    int v, d;
    node(int v, int d) : v(v), d(d) {}
    bool operator < (node other) const {
        return d > other.d; 
    }
};

priority_queue<node> q;

vector<int> g[MAX_SIZE];
int deg[MAX_SIZE];
int dist[MAX_SIZE], visited[MAX_SIZE];

int main() {
    int N, M, i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        deg[u]++;
    }

    for (i = 1; i <= N - 1; ++i) {
        dist[i] = M * 2 + 2;
    }

    q.push(node(N, 0));

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if (visited[curr.v]) continue;
        visited[curr.v] = 1;
        for (auto nv : g[curr.v]) {
            if (deg[nv] + dist[curr.v] < dist[nv]) {
                dist[nv] = deg[nv] + dist[curr.v];
                q.push(node(nv, dist[nv]));
            }

            --deg[nv];
        }
    }

    printf("%d\n", dist[1]);
    return 0;
}