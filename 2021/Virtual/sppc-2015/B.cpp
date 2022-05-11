#include <bits/stdc++.h>
#define MAX_SIZE 261
using namespace std;

const int inf = 1e7;
int dp[MAX_SIZE][MAX_SIZE];
int sm[MAX_SIZE], pm[MAX_SIZE];
char s[MAX_SIZE], p[MAX_SIZE];
int N, M;

int main() {
    int i, j, k;
    scanf("%s%s", s+1, p+1);
    N = strlen(s+1);
    M = strlen(p+1);
    for (i = 1; i <= N; ++i) {
        sm[i] = sm[i-1] + (s[i] - '0');
    }

    for (i = 1; i <= M; ++i) {
        pm[i] = pm[i-1] + (p[i] - 'a' + 1);
    }

    for (i = 0; i <= N; ++i) {
        for (j = 1 ; j <= M; ++j) {
            dp[i][j] = -inf;
        }
    }
    // first i s matches first j p
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (i < pm[j]) break;
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            for (k = 0; k <= i - (pm[j] - pm[j-1]); ++k) {
                dp[i][j] = max(dp[i][j], dp[k][j-1] + sm[i] - sm[i- (pm[j] - pm[j-1])]);
            }
            // printf("(%d,%d)=%d\n", i, j, dp[i][j]);
        }
    }

    printf("%d\n", dp[N][M]);
    return 0;
}