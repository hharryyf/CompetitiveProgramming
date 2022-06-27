#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 20011
const int mod = 998244353;
int N;
int cnt[23][26];
int minn[(1 << 23) + 3][26];
int cost[(1 << 23) + 3];
int dp[(1 << 23) + 3];
char s[23][MAX_SIZE];

int add(int x, int y) {
    int ret = (x + y) % mod; 
    if (ret < 0) ret += mod;
    return ret;
}

int mul(int x, int y) {
    return (1ll * x * y) % mod;
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) scanf("%s", s[i]);
    for (i = 0; i < N; ++i) {
        for (j = 0 ; j < strlen(s[i]); ++j) {
            cnt[i][s[i][j] - 'a']++;
        }

        for (j = 0; j < 26; ++j) {
            minn[1 << i][j] = cnt[i][j];
        }
    }

    for (i = 0; i < (1 << N); ++i) {
        int bt = __builtin_popcount(i);
        if (bt < 2) continue;
        int pos = -1;
        for (j = 0; j < N; ++j) {
            if ((i >> j) & 1) {
                pos = j;
                break;
            }
        }

        for (j = 0 ; j < 26; ++j) {
            minn[i][j] = min(minn[1 << pos][j], minn[(1 << pos) ^ i][j]);
        }
    }

    for(i = 1; i < (1 << N); ++i){
        dp[i] = 1;
        for (j = 0; j < 26; ++j) {
            dp[i] = mul(dp[i], add(minn[i][j], 1));
        }
        int sgn = (__builtin_popcount(i) & 1) ? 1 : -1;
        dp[i] = mul(dp[i], sgn);
    }

    for(i = 0; i < N; ++i){
        for(j = 0; j < (1 << N); ++j){
            if((j >> i) & 1) {
                dp[j] = add(dp[j], dp[j ^ (1 << i)]);
            }
        }
    }


    ll ans = 0;
    for (i = 1 ; i < (1 << N); ++i) {
        int tol = 0;
        ll ret = __builtin_popcount(i);
        for (j = 0 ; j < N; ++j) {
            if ((i >> j) & 1) tol = tol + (j + 1);
        }
        ret = 1ll * ret * dp[i] * tol;
        ans = ans ^ ret;
    }
    printf("%lld\n", ans);
    return 0;
}