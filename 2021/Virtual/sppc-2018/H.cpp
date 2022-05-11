#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
struct edge {
    int from, to, wt, len;
    bool operator < (edge other) const {
        return wt < other.wt;
    }
};

edge edg[MAX_SIZE];
vector<pair<int, ll>> g[MAX_SIZE];
int f[MAX_SIZE], S, E, N, M;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int u, int v) {
    int a = find(u), b = find(v);
    f[a] = b;
}

int mergeroad() {
    int i = 1, j = 1;
    int ret = 0;
    sort(edg + 1, edg + 1 + M);
    while (i <= M) {
        while (j <= M && edg[j].wt == edg[i].wt) {
            unionset(edg[j].from, edg[j].to);
            g[edg[j].from].emplace_back(edg[j].to, edg[j].len);
            g[edg[j].to].emplace_back(edg[j].from, edg[j].len);
            ret = max(ret, edg[j].wt);
            ++j;
        }

        if (find(S) == find(E)) break;
        i = j;
    }
    
    return ret;
}

ll dist[MAX_SIZE];
int visited[MAX_SIZE];

ll dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= N; ++i) dist[i] = 1e16;
    q.push(make_pair(0, S));
    dist[S] = 0;

    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        for (auto np : g[p.second]) {
            int nv = np.first;
            if (!visited[nv]) {
                if (dist[nv] > dist[p.second] + np.second) {
                    dist[nv] = dist[p.second] + np.second;
                    q.push(make_pair(dist[nv], nv));
                }
            }
        }
    }

    return dist[E];
}


int main() {
    int i;
    scanf("%d%d%d%d", &N, &M, &S, &E);
    for (i = 1; i <= N; ++i) f[i] = i;
    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d%d", &edg[i].from, &edg[i].to, &edg[i].wt, &edg[i].len);
    }
    printf("%d\n", mergeroad());
    printf("%lld\n", dijkstra());
    return 0;
}