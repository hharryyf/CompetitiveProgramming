#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200011
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
#include <bitset>
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

ll fac[MAX_SIZE];

ll C(int n, int k) {
    if (n < k) return 0;
    return mul(fac[n], mul(qpow(fac[k], mod - 2), qpow(fac[n-k], mod-2)));
}

int cnt[33];
int suf[33];
ll pw[33];

int main() {
    int i, j, N;
    fac[0] = 1;
    pw[0] = 1;
    for (i = 1; i <= 32; ++i) pw[i] = pw[i-1] * 2;
    for (i = 1; i < MAX_SIZE; ++i) fac[i] = mul(fac[i-1], i);
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        ll v;
        int c = 0;
        scanf("%lld", &v);
        while (v > 0 && v % 2 == 0) {
            v = v / 2;
            c++;
        }

        cnt[c]++;
    }

    for (i = 31; i >= 0; --i) suf[i] += suf[i+1] + cnt[i];

    ll ans = 0;
    for (i = 0 ; i <= 31; ++i) {
        for (ll k = 1 + (i > 0); k <= cnt[i]; k = k + 1 + (i > 0)) {
            ans = add(ans, mul(C(cnt[i], k), qpow(2, suf[i+1])));
        }
    }

    printf("%lld\n", ans);
    return 0;
}