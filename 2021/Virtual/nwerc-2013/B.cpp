#include <bits/stdc++.h>
#define MAX_SIZE 454
using namespace std;

int g[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE];
vector<pair<int, int>> edg;
int N, M;

int main() {
    int i, j, k;
    while (scanf("%d%d", &N, &M) != EOF) {
        int ans = 0;
        edg.clear();
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                g[i][j] = 0;
            }
            scanf("%d", &a[i]);
            ans = max(a[i], ans);
        }

        for (i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u][v] = g[v][u] = 1;
            edg.emplace_back(u, v);
            ans = max(ans, a[u] + a[v]);
        }

        // complete graph 3
        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                for (k = j + 1; k <= N; ++k) {
                    if (g[i][j] && g[j][k] && g[k][i]) {
                        ans = max(ans, a[i] + a[j] + a[k]);
                    }
                }
            }
        }

        // complete graph 4
        for (i = 0 ; i < (int) edg.size(); ++i) {
            for (j = i + 1; j < (int) edg.size(); ++j) {
                int x = edg[i].first, y = edg[i].second, z = edg[j].first, w = edg[j].second;
                if (x == y || x == z || x == w || y == z || y == w || z == w) continue;
                if (g[x][z] && g[x][w] && g[x][y] && g[y][z] && g[z][w] && g[y][w]) {
                    ans = max(ans, a[x] + a[y] + a[z] + a[w]);
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}