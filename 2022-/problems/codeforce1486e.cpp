#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 100011
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
using namespace std;
typedef long long ll;

int dist[MAX_SIZE][51], visited[MAX_SIZE][51], ans[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];

struct state {
    int d, v, pre;
    state(int d=0, int v=0, int pre=-1) : d(d), v(v), pre(pre) {}
    bool operator < (const state &other) const {
        return d > other.d;
    } 
};

const int inf = 1e9 + 7;
priority_queue<state> q;

int main() {
    int i, j, N, M;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 0; j <= 50; ++j) {
            dist[i][j] = inf;
        }
        ans[i] = inf;
    }

    dist[1][0] = 0;

    for (i = 1; i <= M; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    q.push(state(0, 1, 0));
    while (!q.empty()) {
        auto s = q.top();
        q.pop();
        if (visited[s.v][s.pre]) continue;
        visited[s.v][s.pre] = 1;
        for (auto np : g[s.v]) {
            int nxtv = np.first, w = np.second;
            if (s.pre == 0) {
                if (!visited[np.first][w] && dist[np.first][w] > dist[s.v][s.pre]) {
                    dist[np.first][w] = dist[s.v][s.pre];
                    q.push(state(dist[np.first][w], np.first, w));
                }
            } else {
                if (!visited[np.first][0] && dist[np.first][0] > dist[s.v][s.pre] + (s.pre + w) * (s.pre + w)) {
                    dist[np.first][0] = dist[s.v][s.pre] + (s.pre + w) * (s.pre + w);
                    q.push(state(dist[np.first][0], np.first, 0));
                }
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        ans[i] = min(ans[i], dist[i][0]);
        if (ans[i] >= inf) ans[i] = -1;
    }

    for (i = 1; i <= N; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}