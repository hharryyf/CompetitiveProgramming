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

int main() {
    int T;
    scanf("%d", &T);

    vector<ll> ret;
    for (ll i = 3ll; i <= 100000ll; i = i + 2) {
        ret.push_back(((i * i - 1) / 2 + 1));
    }

    while (T-- > 0) {
        ll N;
        scanf("%lld", &N);
        if (N < ret.front()) {
            printf("0\n");
        } else {
            int idx = upper_bound(ret.begin(), ret.end(), N) - ret.begin();
            // printf("%lld\n", ret[idx]);
            printf("%d\n", idx);
        }
    }
    return 0;
}