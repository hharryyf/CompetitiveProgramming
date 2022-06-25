#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 20000011
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



int prime[MAX_SIZE];
bool visited[MAX_SIZE];

int maxn = 20000000;

ll calc(int c, int d, int x, int g) {
    // if (((1ll * d * g + x) * g) % c != 0) return 0;
    if ((1ll * d * g + x) % (1ll * g * c) != 0) return 0;
    debug("calculate %d %d %d %d get %d\n", c, d, x, g, (x + d * g) / (g * c));
    return prime[(1ll * d * g + x) / (1ll * g * c)];
}

int solve(int c, int d, int x){
    ll ans = 0;
    for (int g = 1; g <= sqrt(x); ++g) {
        if (x % g == 0) {
            if (g * g == x) {
                ans += calc(c, d, x, g);
            } else {
                ans += calc(c, d, x, g);
                ans += calc(c, d, x, x / g);
            }
        }
    }

    return ans;
}

int main() {
    int T, i, j;
    for (i = 1; i <= maxn; ++i) {
        prime[i] = 1;
    }
    for (i = 2; i <= maxn; ++i) {
        if (!visited[i]) {
            for (j = 1; j * i <= maxn; ++j) {
                visited[i * j] = 1;
                prime[i * j] *= 2;
            }
        }
    }

    scanf("%d", &T);
    while (T-- > 0) {
        int c, d, x;
        scanf("%d%d%d", &c, &d, &x);
        printf("%d\n", solve(c, d, x));
    }
    return 0;
}