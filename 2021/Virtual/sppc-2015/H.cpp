#include <bits/stdc++.h>
#define MAX_SIZE 2511
using namespace std;
typedef long long ll;
vector<pair<int, ll>> g[MAX_SIZE];
ll dist[MAX_SIZE], h[MAX_SIZE];
int visited[MAX_SIZE];
struct edge {
    int from, to;
    ll cost;
};

vector<edge> edg;

int W, H;

int idx(int x, int y) {
    return (x - 1) * W + y;
}

ll dijkstra(int src) {
    int i;
    memset(visited, 0, sizeof(visited));
    for (i = 1; i <= W * H; ++i) dist[i] = 1e13;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    dist[src] = 0;
    q.push({0, src});
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        for (auto nv : g[p.second]) {
            if (!visited[nv.first] && dist[nv.first] > p.first + nv.second) {
                dist[nv.first] = p.first + nv.second;
                q.push({dist[nv.first], nv.first});
            }
        }
    }
    ll ret = 0;
    for (i = 1; i <= W * H; ++i) {
        ret += dist[i];
    }

    return ret;
}

int main() {
    int i, j;
    scanf("%d%d", &W, &H);
    // case north
    for (i = 1; i <= H; ++i) {
        for (j = 1; j <= W; ++j) {
            int c;
            scanf("%d", &c);
            if (i > 1) {
                edg.push_back(edge{idx(i, j), idx(i - 1, j), c});
            }
        }
    }

    // case west
    for (i = 1; i <= H; ++i) {
        for (j = 1; j <= W; ++j) {
            int c;
            scanf("%d", &c);
            if (j > 1) {
                edg.push_back(edge{idx(i, j), idx(i, j - 1), c});
            }
        }
    }

    // case south
    for (i = 1; i <= H; ++i) {
        for (j = 1; j <= W; ++j) {
            int c;
            scanf("%d", &c);
            if (i < H) {
                edg.push_back(edge{idx(i, j), idx(i + 1, j), c});
            }
        }
    }

    // case east
    for (i = 1; i <= H; ++i) {
        for (j = 1; j <= W; ++j) {
            int c;
            scanf("%d", &c);
            if (j < W) {
                edg.push_back(edge{idx(i, j), idx(i, j + 1), c});
            }
        }
    }

    for (i = 1; i <= H; ++i) {
        for (j = 1; j <= W; ++j) {
            edg.push_back(edge{0, idx(i, j), 0});
        }
    }

    for (i = 1 ; i <= W * H; ++i) {
        h[i] = 1e13;
    }

    for (i = 1; i <= W * H; ++i) {
        for (auto e : edg) {
            if (h[e.to] > h[e.from] + e.cost) {
                h[e.to] = h[e.from] + e.cost;
            }
        }
    }

    for (auto e : edg) {
        if (e.from == 0) continue;
        g[e.from].emplace_back(e.to, e.cost - h[e.to] + h[e.from]);
    }

    ll ans = 0, tol = (W * H) * (W * H - 1);
    for (i = 1; i <= W * H; ++i) {
        ans += dijkstra(i);
    }


    if (ans % tol != 0) {
        printf("%lld\n", ans / tol + 1);
    } else {
        printf("%lld\n", ans / tol);
    }
    return 0;
}