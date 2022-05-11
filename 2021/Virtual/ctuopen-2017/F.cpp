#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

int dp[MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE], N;

int solve(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int f1 = solve(l+1, r), f2 = solve(l, r - 1);
    int f = -1;
    if (a[l] == a[r]) {
        f = 1 + solve(l + 1, r - 1);
    }

    return dp[l][r] = max(f, max(f1, f2));
}

int main() {
    while (scanf("%d", &N) != EOF) {
        int i, j;
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                dp[i][j] = -1;
            }
        }

        printf("%d\n", solve(1, N));
    }
    return 0;
}