#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 524312
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

int parent[MAX_SIZE][20];
int a[MAX_SIZE], c[MAX_SIZE];

int main() {
    int Q, i;
    scanf("%d%d%d", &Q, &a[1], &c[1]);
    for (i = 2; i <= Q + 1; ++i) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int v;
            scanf("%d%d%d", &v, &a[i], &c[i]);
            v += 1;
            parent[i][0] = v;
            for (int j = 1; j <= 19; ++j) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        } else {
            int v, w;
            ll ans = 0, tol = 0;
            scanf("%d%d", &v, &w);
            v += 1;
            while (a[v] > 0 && w > 0) {
                int curr = v;
                for (int j = 19; j >= 0; --j) {
                    if (a[parent[curr][j]] != 0) {
                        curr = parent[curr][j];
                    }
                }

                int tk = min(a[curr], w);
                ans = ans + 1ll * tk * c[curr];
                tol += tk;
                w -= tk;
                a[curr] -= tk;
            }

            printf("%lld %lld\n", tol, ans);
            fflush(stdout);
        }
    }
    return 0;
}