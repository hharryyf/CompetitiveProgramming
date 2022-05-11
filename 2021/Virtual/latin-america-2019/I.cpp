#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;

const int mod = 1e9 + 7;
vector<int> g[MAX_SIZE];
int dp[MAX_SIZE];
int visited[MAX_SIZE];
int cnt, N, L;

int add(int v, int u) {
    return (v + u) % mod;
}

int dfs(int v) {
    if (visited[v]) return dp[v];
    visited[v] = 1;
    if (v > L) cnt++;
    if (g[v].empty()) {
        dp[v] = 1;
        return 1;
    }
    for (auto nv : g[v]) {
        dp[v] = add(dfs(nv), dp[v]);
    }
    return dp[v];
}

int main() {
    int i;
    scanf("%d%d", &N, &L);
    for (i = 1; i <= L; ++i) {
        int K;
        scanf("%d", &K);
        while (K-- > 0) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
        }
    }

    int ans = dfs(1);
    printf("%d %d\n", ans, cnt);
    return 0;
}