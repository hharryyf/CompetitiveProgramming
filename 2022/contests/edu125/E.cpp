#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 511
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
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
using namespace std;
typedef long long ll;

const ll mod = 998244353;

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


ll dp[MAX_SIZE][MAX_SIZE];
ll fac[MAX_SIZE], ifac[MAX_SIZE];
int N, K;

ll C(int n, int k) {
    if (n < k) return 0;
    return mul(mul(fac[n], ifac[k]), ifac[n-k]);
}

int main() {
    int i, j, k;
    scanf("%d%d", &N, &K);
    dp[0][0] = 1;
    fac[0] = ifac[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = mul(fac[i-1], i);
        ifac[i] = mul(ifac[i-1], qpow(i, mod - 2));
    }

    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < K; ++j) {
            for (k = 0; k < N - i; ++k) {
                dp[i+k][j+1] = add(dp[i+k][j+1], mul(mul(dp[i][j], C(N - i - 1, k)), qpow(K - j, k * (k - 1) / 2 + k * i)));
            }
        }
    }

    printf("%lld\n", dp[N - 1][K]);
    return 0;
}