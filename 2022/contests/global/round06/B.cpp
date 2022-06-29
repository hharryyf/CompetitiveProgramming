#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 111
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

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll N;
        scanf("%lld", &N);
        if (N < 15) {
            printf("NO\n");
        } else if (N >= 15 && N < 21) {
            printf("YES\n");
        } else {
            /*
                see if 21 - 1..6 + 14 * x = N
            */
            bool ok = false;
            for (int i = 1; i <= 6; ++i) {
                if ((N - 21 + i) % 14 == 0 && (N - 21 + i) / 14 >= 0) {
                    ok = true;
                }
            }

            if (ok) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}