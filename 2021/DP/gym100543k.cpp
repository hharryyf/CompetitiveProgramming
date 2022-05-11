#include <bits/stdc++.h>
#define MAX_SIZE 150011
using namespace std;

int dp[MAX_SIZE][10], N;
int visited[MAX_SIZE][10];
pair<int, int> item[MAX_SIZE];

int dfs(int pos, int k) {
    if (pos > N) return 0;
    if (visited[pos][k]) return dp[pos][k];
    visited[pos][k] = 1;
    int ret = dfs(pos + 1, k);
    int ret2 = item[pos].first - item[pos].second;
    if (k > 0) {
        ret2 = min(ret2, dfs(pos + 1, k - 1) - item[pos].second);
    }
    ret = max(ret, ret2);
    return dp[pos][k] = ret;
}

void solve() {
    int K, i;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &item[i].first, &item[i].second);
    }

    sort(item + 1, item + 1 + N);
    memset(dp, 0, sizeof(dp));
    memset(visited, 0, sizeof(visited));
    printf("%d\n", dfs(1, K));
}   

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        solve();
    }
    return 0;
}