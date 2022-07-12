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
ll a[MAX_SIZE];
ll X;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d%lld", &N, &X);
        for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
        sort(a + 1, a + 1 + N);
        ll day = 0, sm = 0, ret = 0;
        for (i = 1; i <= N; ++i) {
            sm += a[i];
        }

        for (i = N; i >= 1; --i) {
            // sm + (K - 1) * i <= X
            // K <= (X - sm) / i + 1
            if (X < sm) {
                sm -= a[i];
                continue;
            }
            ll K = (X - sm) / i + 1;
            ret = ret + max(K - day, 0ll) * i;
            day = day + max(K - day, 0ll);
            debug("%lld %lld %lld\n", sm, day, K);
            sm -= a[i];
            
        }

        printf("%lld\n", ret);
    }
    return 0;
}