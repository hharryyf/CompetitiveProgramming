#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
typedef long long ll;
#define MAX_SIZE 1000011
using namespace std;

int a[MAX_SIZE], d[MAX_SIZE], sz[MAX_SIZE], ok[MAX_SIZE], X, Y;
vector<int> g[MAX_SIZE];

void dfs(int v, int pre) {
    sz[v] = a[v];
    for (auto nv : g[v]) {
        if (nv != pre) {
            d[nv] = d[v] + 1;
            dfs(nv, v);
            sz[v] += sz[nv];
        }
    }

    ok[v] = (sz[v] >= 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, K, i;
        scanf("%d%d", &N, &K);
        for (i = 1; i <= N; ++i) {
            ok[i] = d[i] = a[i] = sz[i] = 0;
            g[i].clear();
        }

        scanf("%d%d", &X, &Y);

        for (i = 1; i <= K; ++i) {
            int v;
            scanf("%d", &v);
            a[v] = 1;
        }

        for (i = 1; i < N; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        a[X] = a[Y] = 1;
        dfs(X, 0);
        ll ans = 0;
        for (i = 1; i <= N; ++i) {
            if (ok[i]) {
                ans += 1;
            }
        }

        ans--;

        ans *= 2;

        ans -= d[Y];

        printf("%lld\n", ans);
    }
    return 0;
}