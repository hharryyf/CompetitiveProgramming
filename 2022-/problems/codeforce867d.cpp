#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 5111
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
typedef long double ld;
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

ld dp[52][MAX_SIZE];
int f[52], s[52];
ld p[52];
int N, R;

bool check(ld curr) {
    int i, j;
    for (i = 1; i <= N + 1; ++i) {
        for (j = R + 1; j < MAX_SIZE; ++j) {
            dp[i][j] = curr;
        }
    }

    for (i = N; i >= 1; --i) {
        for (j = 0 ; j <= R; ++j) {
            dp[i][j] = min(curr, (dp[i + 1][j + f[i]] + f[i]) * p[i] + (dp[i + 1][j + s[i]] + s[i]) * (1.0 - p[i]));
        }
    }
    return dp[1][0] < curr;
}

int main() {
    int i;
    scanf("%d%d", &N, &R);
    for (i = 1; i <= N; ++i) {
        cin >> f[i] >> s[i] >> p[i];
        p[i] *= 0.01;
    }

    ld low = 0, high = 1e9, ans = 1e9;
    for (i = 0 ; i < 180; ++i) {
        ld mid = (low + high) * 0.5;
        if (check(mid)) {
            ans = mid;
            high = mid;
        } else {
            low = mid;
        }
    }

    printf("%.12Lf\n", ans);
    return 0;
}