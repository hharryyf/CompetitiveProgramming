#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300000011
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

bitset<MAX_SIZE> bt;

int a, b;

int main() {
    int i, j;
    scanf("%d%d", &a, &b);
    bt.set();
    for (i = 3; i * i <= b; i = i + 2) {
        if (bt[i]) {
            for (j = i * i; j <= b; j += 2 * i) {
                bt[j] = 0;
            }
        }
    }

    int ans = (a <= 2 && b >= 2);

    for (i = 5; i <= b; i = i + 4) {
        if (i >= a && bt[i]) ans++;
    }

    printf("%d\n", ans);
    return 0;
}