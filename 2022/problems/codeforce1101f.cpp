#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 402
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


const int inf = 1e9 + 7;
int dp[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE];
int N;

int main() {
    int i, j, k;
    int Q;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= N; ++i) {
        for (j = i; j <= N; ++j) {
            if (i == j) continue;
            for (k = 1; k <= N; ++k) {
                dp[i][j][k] = inf;
            }

            dp[i][j][0] = a[j] - a[i]; 
        }
    }

    for (k = 1; k <= N; ++k) {
        for (i = 1; i <= N; ++i) {
            int opt = i;
            for (j = i + 1; j <= N; ++j) {
                while (opt < j && max(dp[i][opt][k-1], a[j] - a[opt]) > max(dp[i][opt + 1][k-1], a[j] - a[opt + 1])) {
                    opt++;
                }

                dp[i][j][k] = min(dp[i][j][k], max(dp[i][opt][k-1], a[j] - a[opt]));
            }
        }
    }

    ll ans = 0;
    while (Q-- > 0) {
        int s, f, c, r;
        scanf("%d%d%d%d", &s, &f, &c, &r);
        ans = max(ans, 1ll * dp[s][f][r] * c);
    }

    printf("%lld\n", ans);
    return 0;
}