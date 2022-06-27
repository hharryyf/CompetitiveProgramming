#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1011
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

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int N;
ll dp[MAX_SIZE];
ll a[MAX_SIZE], f[MAX_SIZE << 1];

ll C(int n, int k) {
    if (n < k) return 0;
    return mul(f[n],  mul(qpow(f[k], mod - 2), qpow(f[n-k], mod - 2)));
}

int main() {
    int i, j;
    ll ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
    f[0] = 1;
    dp[N + 1] = 1;
    for (i = 1; i < (MAX_SIZE << 1); ++i) f[i] = mul(f[i-1], i);

    for (i = N; i >= 1; --i) {
        if (a[i] > 0) {
            // [a[i], a[i] numbers | j]
            for (j = i + a[i] + 1; j <= N + 1; ++j) {
                dp[i] = add(dp[i], mul(dp[j], C(j - i - 1, a[i])));
            }
        }

        ans = add(ans, dp[i]);
    }

    printf("%lld\n", ans);
    return 0;
}