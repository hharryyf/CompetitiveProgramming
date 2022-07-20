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

int mx[MAX_SIZE];
int a[MAX_SIZE];

int main() {
    int T, N, K;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        scanf("%d%d", &N, &K); 
        memset(mx, 0, sizeof(mx)); 
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        for (i = 1; i <= N; ++i) {
            int up = 300000;
            for (j = 1; j <= min(a[i], K); j = (a[i] / (a[i] / j)) + 1) {
                int q = a[i] / j;
                mx[q + 1] = max(mx[q + 1], up);
                up = q;
            }

            mx[1] = max(mx[1], up);
        }

        for (i = 1; i <= a[1]; ++i) {
            mx[i] = max(mx[i], mx[i-1]);
        }

        int ans = 300000;
        for (i = 1; i <= a[1]; ++i) {
            ans = min(ans, mx[i] - i);
        }

        printf("%d\n", ans);
   }
    return 0;
}