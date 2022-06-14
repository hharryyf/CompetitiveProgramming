#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
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

const ll mod = 1e18 + 7;

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


const ll inf = mod;
ll dp[MAX_SIZE][11];
ll a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int Q, N, i, j, k;
    scanf("%d", &Q);
    while (Q-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%lld%lld", &a[i], &b[i]);
            for (j = 0 ; j <= 10; ++j) {
                dp[i][j] = inf;
            }
        }

        for (i = 0; i <= 10; ++i) {
            dp[1][i] = b[1] * i;
        }

        for (i = 1; i < N; ++i) {
            for (j = 0 ; j <= 10; ++j) {
                for (k = 0 ; k <= 10; ++k) {
                    if (a[i] + j != a[i+1] + k) {
                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + b[i + 1] * k);
                    }
                }
            }
        }

        ll ans = dp[N][0];
        for (i = 1; i <= 10; ++i) ans = min(ans, dp[N][i]);

        for (i = 1; i <= N; ++i) {
            for (j = 0 ; j <= 3; ++j) {
                debug("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
            }
        }
        printf("%lld\n", ans);
    } 
    return 0;
}