#include <bits/stdc++.h>
#define MAX_SIZE 8011
using namespace std;

const int inf = 1e9;
int M;
vector<pair<pair<int, int>, int>> g[MAX_SIZE];
int dist[MAX_SIZE], visited[MAX_SIZE];
int edg[MAX_SIZE][5];

int dijkstra(int src, int target, int bad) {
    if (g[src].empty()) return inf;
    int ret = inf;
    memset(visited, 0, sizeof(visited));
    memset(dist, 63, sizeof(dist));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, src));
    dist[src] = 0;
    while (!q.empty()) {
        auto p = q.top();
        q.pop();
        if (visited[p.second]) continue;

        if (p.first + edg[bad][4] > ret) break;
        visited[p.second] = 1;
        dist[p.second] = p.first;
        
        if (p.second == target) {
            ret = min(ret, p.first + edg[bad][4]);
        }

        for (auto np : g[p.second]) {
            int nv = np.first.first, w = np.first.second, id = np.second;
            if (visited[nv] || id == bad) continue;
            if (dist[nv] > dist[p.second] + w) {
                dist[nv] = dist[p.second] + w;
                q.push(make_pair(dist[nv], nv));
            } 
        }
    }

    return ret;
}

void solve() {
    int i, j, ans = inf;
    scanf("%d", &M); 
    for (i = 1; i < MAX_SIZE; ++i) g[i].clear();
    vector<pair<int, int>> tmp, disc;
    for (i = 1; i <= M; ++i) {
        for (j = 0 ; j < 5; ++j) {
            scanf("%d", &edg[i][j]);
        }

        tmp.emplace_back(edg[i][0], edg[i][1]);
        tmp.emplace_back(edg[i][2], edg[i][3]);
    }

    sort(tmp.begin(), tmp.end());

    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    for (i = 1; i <= M; ++i) {
        auto p = make_pair(edg[i][0], edg[i][1]);
        int id1 = lower_bound(disc.begin(), disc.end(), p) - disc.begin() + 1;
        int id2 = lower_bound(disc.begin(), disc.end(), make_pair(edg[i][2], edg[i][3])) - disc.begin() + 1;
        if (id1 == id2) {
            ans = min(ans, edg[i][4]);
        } else {
            g[id1].emplace_back(make_pair(id2, edg[i][4]), i);
            g[id2].emplace_back(make_pair(id1, edg[i][4]), i);
        }
    }

    for (i = 1; i <= M; ++i) {
        int id1 = lower_bound(disc.begin(), disc.end(), make_pair(edg[i][0], edg[i][1])) - disc.begin() + 1;
        int id2 = lower_bound(disc.begin(), disc.end(), make_pair(edg[i][2], edg[i][3])) - disc.begin() + 1; 
        ans = min(ans, dijkstra(id1, id2, i));
    }

    if (ans == inf) {
        printf("0\n");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}