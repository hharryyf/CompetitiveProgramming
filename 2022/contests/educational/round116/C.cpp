#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

ll pw[12];
bool ok[12];

void init() {
    pw[0] = 1;
    int i;
    for (i = 1; i <= 11; ++i) pw[i] = pw[i-1] * 10;
}

ll step(ll x) {
    int i;
    ll ret = 0;
    for (i = 11; i >= 0 && x > 0; --i) {
        if (x >= pw[i] && ok[i]) {
            ret += x / pw[i];
            x = x % pw[i];
        }
    }

    return ret;
}


int main() {
    init();
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        int N;
        ll K;
        scanf("%d%lld", &N, &K);
        string s = "999999999999999999";
        memset(ok, false, sizeof(ok));
        for (i = 0 ; i < N; ++i) {
            int v;
            scanf("%d", &v);
            ok[v] = true;
        }

        for (i = 0 ; i < (int) s.length(); ++i) {
            for (j = 0 ; j <= 9; ++j) {
                s[i] = j + '0';
                if (step(atoll(s.c_str())) > K) {
                    break;
                }
            }
        }

        printf("%lld\n", atoll(s.c_str()));
    }
    return 0;
}