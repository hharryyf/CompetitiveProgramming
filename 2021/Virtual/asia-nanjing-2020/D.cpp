#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

vector<int> g[MAX_SIZE];
int N, M, tol = 0;
int deg[MAX_SIZE], visited[MAX_SIZE];
vector<pair<int, int>> ans;

void dfs(int v) {
    visited[v] = 1;
    ++tol;
    random_shuffle(g[v].begin(), g[v].end());
    for (auto nv : g[v]) {
        if (deg[v] >= N / 2) break;
        if (!visited[nv]) {
            ans.emplace_back(v, nv);
            deg[v]++, deg[nv]++;
            dfs(nv);
        }
    }
}

bool check(int root) {
    int i;
    ans.clear();
    for (i = 1; i <= N; ++i) {
        deg[i] = visited[i] = 0;
    }

    tol = 0;

    dfs(root);

    return tol == N;
}

int main() {
    srand(time(NULL));
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        int ok = 0;
        scanf("%d%d", &N, &M);
        for (i = 1; i <= N; ++i) g[i].clear();
        for (i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (i = 1; i <= 300; ++i) {
            int root = (1ll * rand() * rand()) % N + 1;
            if (check(root)) {
                ok = 1;
                printf("Yes\n");
                for (auto p : ans) {
                    printf("%d %d\n", p.first, p.second);
                }
                break;
            }
        }

        if (!ok) {
            printf("No\n");
        }
    }
    return 0;
}