#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
// dp[i][j] = number of ways to type the first i characters with the last character as j
ll dp[10011][753], sm[10011][753];
ll T[753][753], p[10011];
int N, K;
ll L;

int main() {
    int i, j;
    scanf("%d%lld", &K, &L);
    

    for (i = 1; i <= K; ++i) {
        for (j = 1; j <= K; ++j) {
            scanf("%lld", &T[i][j]);
        }
    }

    scanf("%d", &N);
    for (i = 1; i <= N-1; ++i) {
        scanf("%lld", &p[i]);
    }

    for (i = 1; i <= K; ++i) {
        dp[N][i] = 1;
        sm[N][i] = i;
    }

    for (i = N - 1; i >= 1; --i) {
        for (j = 1; j <= K; ++j) {
            int low = lower_bound(T[j] + 1, T[j] + 1 + K, p[i] - L) - T[j];
            int high = upper_bound(T[j] + 1, T[j] + 1 + K, p[i] + L) - T[j];
            ll L = low > 0 ? sm[i + 1][low - 1] : 0;
            ll R = high > 0 ? sm[i + 1][high - 1] : 0;
            dp[i][j] = (R - L + mod) % mod;
        }

        for (j = 1; j <= K; ++j) {
            sm[i][j] = (sm[i][j - 1] + dp[i][j]) % mod;
        }
    }

    printf("%lld\n", sm[1][K]);
    return 0;
}