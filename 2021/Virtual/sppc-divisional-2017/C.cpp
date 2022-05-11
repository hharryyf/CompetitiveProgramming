#include <bits/stdc++.h>

using namespace std;

char s[12][25];
int dp[21][1029];
int N;

int solve(char target[]) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    int len = strlen(target + 1), i, j, k;
    if (len != N) {
        return 0;
    }

    for (j = 0 ; j < N; ++j) {
        for (i = 0 ; i < (1 << N); ++i) {
            for (k = 0; k < N; ++k) {
                if (((1 << k) & i) == 0 && j == __builtin_popcount(i)) {
                    bool has = false;
                    //printf("check %d\n", k);
                    for (int m = 1; m <= (int) strlen(s[k] + 1); ++m) {
                        if (s[k][m] == target[j+1]) {
                            has = true;
                            break;
                        }
                    }

                    if (has) {
                        dp[j + 1][i | (1 << k)] += dp[j][i];
                    }
                }
            }
        }
    }

    return dp[N][(1 << N) - 1];
}   

char target[25];

int main() {
    int i, K;
    scanf("%d%d", &N, &K);
    for (i = 0; i < N; ++i) scanf("%s", s[i] + 1);
    for (i = 1; i <= K; ++i) {
        scanf("%s", target + 1);
        printf("%d\n", solve(target));
    }
    return 0;
}