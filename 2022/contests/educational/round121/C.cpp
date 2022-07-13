#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 111
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

ll dp[MAX_SIZE];
ll h[MAX_SIZE], k[MAX_SIZE];
ll le[MAX_SIZE][MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j;
        scanf("%d", &N);
        k[0] = -1e18;
        for (i = 1; i <= N; ++i) {
            dp[i] = 1e18;
            scanf("%lld", &k[i]);
        }

        for (i = 1; i <= N; ++i) scanf("%lld", &h[i]);
        
        for (i = 1; i <= N; ++i) {
            le[i][i] = h[i];
        }

        for (i = 1; i <= N; ++i) {
            for (j = i - 1; j >= 1; --j) {
                le[j][i] = max(le[j+1][i], h[j] + (k[i] - k[j]));
            }
        }

        for (i = 1; i <= N; ++i) {
            for (j = 0; j < i; ++j) {
                if (k[i] - le[j+1][i] >= k[j]) {
                    dp[i] = min(dp[i], dp[j] + le[j+1][i] * (le[j+1][i] + 1) / 2);
                }
            }
        }

        printf("%lld\n", dp[N]);
    }
    return 0;
}