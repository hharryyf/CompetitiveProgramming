#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 524312
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

int a[111];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i;
        scanf("%d", &N);
        int mn = 0;
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        mn = a[1];

        for (i = 1; i <= N; ++i) {
            mn = min(mn, a[i]);
        }

        int ans = 0;
        for (i = 1; i <= N; ++i) {
            if (mn != a[i]) {
                ans++;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}