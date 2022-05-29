#include <bits/stdc++.h>
#define MAX_SIZE 10111
using namespace std;

int dp[102][MAX_SIZE];
int a[102], b[102];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        memset(dp, 0, sizeof(dp));
        int N, i, j;
        int sm = 0;
        long long ans = 0;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            sm += a[i];
            ans = ans + a[i] * a[i];
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &b[i]);
            sm += b[i];
            ans = ans + b[i] * b[i];
        }

        dp[0][0] = 1;
        for (i = 0; i < N; ++i) {
            for (j = 0; j < MAX_SIZE; ++j) {
                if (dp[i][j] && j + a[i+1] < MAX_SIZE && j + b[i+1] < MAX_SIZE) {
                    dp[i+1][j + a[i+1]] = 1;
                    dp[i+1][j + b[i+1]] = 1;
                }
            }
        }

        long long curr = 1e18;
        for (i = 0; i <= sm; ++i) {
            if (dp[N][i]) {
                curr = min(curr, 1ll * i * i + (sm - i) * (sm - i));
            }
        }

        ans = ans * (N - 2) + curr;
        printf("%lld\n", ans);
    }
    return 0;
}