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

int N, M;
ll K;
ll ans = 0;
ll dp[MAX_SIZE];
ll a[MAX_SIZE];
bool ok[MAX_SIZE];

int main() {
    int i, j;
    scanf("%d%d%lld", &N, &M, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &a[i]);
    }  

    for (j = 1; j <= M; ++j) {
        for (i = j; i <= N; i = i + M) {
            ok[i] = true;
            a[i] -= K;
        }

        for (i = 1; i <= N; ++i) dp[i] = 0;
        for (i = 1; i <= N; ++i) {
            dp[i] = max(dp[i-1] + a[i], a[i]);
            if (ok[i]) ans = max(ans, dp[i]);
        }

        for (i = j; i <= N; i = i + M) {
            ok[i] = false;
            a[i] += K;
        }
    }

    printf("%lld\n", ans);
    return 0;
}