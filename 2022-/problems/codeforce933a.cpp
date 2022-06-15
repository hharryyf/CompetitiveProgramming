#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 2011
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

inline ll add(ll x,ll y){
    return ((x + y) % mod + mod) % mod;
}

inline ll mul(ll x,ll y){
    return x * y % mod;
}

inline ll qpow(ll x,ll n){
    ll ret= 1;
    while(n > 0){
        if(n & 1) ret = mul(ret, x);
        x = mul(x, x);
        n >>= 1;
    }

    return ret;
}

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int N;

int cnt[MAX_SIZE][2];
int dp[MAX_SIZE][MAX_SIZE];
int dp2[MAX_SIZE][2];
int a[MAX_SIZE];

int query(int dim, int l, int r) {
    if (l > r) return 0;
    return cnt[r][dim] - cnt[l-1][dim];
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    for (i = 1; i <= N; ++i) {
        memset(dp2, 0, sizeof(dp2));
        dp2[i][a[i]] = 1;
        dp[i][i] = 1;
        for (j = i - 1; j >= 1; --j) {
            if (a[j] == 1) {
                dp2[j][1] = max(dp2[j+1][1], dp2[j+1][0]) + 1;
                dp2[j][0] = dp2[j+1][0];
            } else {
                dp2[j][0] = dp2[j+1][0] + 1;
                dp2[j][1] = dp2[j+1][1];
            }

            dp[j][i] = max(dp[j+1][i], max(dp2[j][0], dp2[j][1]));
        }

        cnt[i][a[i]] = cnt[i-1][a[i]] + 1;
        cnt[i][1 - a[i]] = cnt[i-1][1 - a[i]];
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= i; ++j) {
            debug("dp[%d][%d] = %d\n", j, i, dp[j][i]);
        }
    }
    int ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= i; ++j) {
            // [1, j - 1] [j, i] [i + 1, N]
            debug("%d %d %d %d %d\n", i, j, query(0, 1, j - 1), query(1, i + 1, N), dp[j][i]);
            ans = max(ans, query(0, 1, j - 1) + query(1, i + 1, N) + dp[j][i]);
        }
    }

    printf("%d\n", ans);
    return 0;
}