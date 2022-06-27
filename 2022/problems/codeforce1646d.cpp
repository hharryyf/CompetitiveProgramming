#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

vector<int> g[MAX_SIZE];
int w[MAX_SIZE], N;
int dp[MAX_SIZE][2][2], ans[MAX_SIZE];
vector<pair<int, int>> decision[MAX_SIZE][2];

void dfs(int v, int pre) {
    bool child = true;
    for (auto nv : g[v]) {
        if (nv != pre) {
            child = false;
            dfs(nv, v);
        }
    }

    if (child) {
        dp[v][0][0] = 0;
        dp[v][0][1] = 1;
        dp[v][1][0] = 1;
        dp[v][1][1] = w[v];
    } else {
        dp[v][1][0] = 1;
        dp[v][1][1] = w[v];
        dp[v][0][0] = 0;
        dp[v][0][1] = 1;
        for (auto nv : g[v]) {
            if (nv != pre) {
                dp[v][1][0] += dp[nv][0][0];
                dp[v][1][1] += dp[nv][0][1];
                decision[v][1].emplace_back(nv, 0);
                if (dp[nv][1][0] > dp[nv][0][0] || (dp[nv][1][0] == dp[nv][0][0] && dp[nv][1][1] < dp[nv][0][1])) {
                    dp[v][0][0] += dp[nv][1][0];
                    dp[v][0][1] += dp[nv][1][1];
                    decision[v][0].emplace_back(nv, 1);
                } else {
                    dp[v][0][0] += dp[nv][0][0];
                    dp[v][0][1] += dp[nv][0][1];
                    decision[v][0].emplace_back(nv, 0);
                }
            }
        }
    }

    debug("dp[%d][%d][%d] = %d, dp[%d][%d][%d] = %d, dp[%d][%d][%d] = %d, dp[%d][%d][%d] = %d\n", v, 0, 0, dp[v][0][0], v, 0, 1, dp[v][0][1], v, 1, 0, dp[v][1][0], v, 1, 1, dp[v][1][1]);
}

void construct(int v, int c) {
    if (c == 1) {
        ans[v] = w[v];
    } else {
        ans[v] = 1;
    }

    for (auto np : decision[v][c]) {
        construct(np.first, np.second);
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (N == 2) {
        printf("2 2\n1 1\n");
        return 0;
    }

    for (i = 1; i <= N; ++i) {
        w[i] = (int) g[i].size();
        dp[i][0][1] = dp[i][1][1] = 1e8; 
    }

    dfs(1, 0);

    if (dp[1][1][0] > dp[1][0][0] || (dp[1][1][0] == dp[1][0][0] && dp[1][1][1] < dp[1][0][1])) {
        printf("%d %d\n", dp[1][1][0], dp[1][1][1]);
        construct(1, 1);
    } else {
        printf("%d %d\n", dp[1][0][0], dp[1][0][1]);
        construct(1, 0);
    }

    for (i = 1; i <= N; ++i) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}