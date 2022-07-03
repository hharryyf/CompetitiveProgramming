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

ll dist(int x, int y) {
    return llabs(a[x] - a[y]) + llabs(x - y);
}

bool check(int l, int r) {
    if (r - l <= 1) return true;
    for (int i = l; i <= r; ++i) {
        for (int j = i + 1; j <= r; ++j) {
            for (int k = j + 1; k <= r; ++k) {
                if (dist(i, j) + dist(j, k) == dist(i, k)) return false;
                if (dist(i, k) + dist(i, j) == dist(j, k)) return false;
                if (dist(i, k) + dist(j, k) == dist(i, j)) return false;
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        int ans = 0;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            for (j = i; j >= 1; --j) {
                if (check(j, i)) {
                    ans++;
                } else {
                    break;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}