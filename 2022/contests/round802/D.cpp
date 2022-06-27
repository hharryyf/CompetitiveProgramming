#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 3000011
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

int N;
ll pre[MAX_SIZE];
ll mx[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &pre[i]);
        pre[i] += pre[i-1];
    }

    // table[i] i tab minimum time
    
    vector<ll> table = vector<ll>(N + 1, 0);   
    for (i = 1; i <= N; ++i) {
        mx[i] = max(mx[i-1], (pre[i] / i) + (pre[i] % i != 0));
    }

    for (i = 1; i <= N; ++i) {
        table[i] = max(mx[i-1], (pre[N] / i) + (pre[N] % i != 0));
        table[i] *= -1;
    }

    table[0] = -1e18;

    /*for (i = 1; i <= N; ++i) {
        printf("%lld ", table[i]);
    }*/
    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        ll t;
        scanf("%lld", &t);
        t *= -1;
        if (t > table.back()) {
            printf("-1\n");
        } else {
            auto idx = lower_bound(table.begin(), table.end(), t) - table.begin();
            printf("%d\n", idx);
        }
    }
    return 0;
}