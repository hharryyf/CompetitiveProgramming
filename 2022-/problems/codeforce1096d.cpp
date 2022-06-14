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

const ll mod = 1e18 + 7;

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

char s[MAX_SIZE];
int N;
// [0] --> _
// [1] --> h
// [2] --> ha
// [3] --> har
ll dp[MAX_SIZE][4];
ll a[MAX_SIZE];
const ll inf = mod;

int main() {
    int i, j;
    scanf("%d", &N);
    scanf("%s", s + 1);
    for (i = 0; i <= N; ++i) {
        for (j = 0 ; j <= 3; ++j) {
            dp[i][j] = inf;
        }
    }

    for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);

    dp[0][0] = 0;

    for (i = 0; i < N; ++i) {
        if (s[i+1] == 'h') {
            dp[i+1][0] = dp[i][0] + a[i+1];
            dp[i+1][1] = min(dp[i][0], dp[i][1]);
            dp[i + 1][2] = dp[i][2];
            dp[i + 1][3] = dp[i][3];
        } else if (s[i + 1] == 'a') {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][1] + a[i+1];
            dp[i+1][2] = min(dp[i][2], dp[i][1]);
            dp[i+1][3] = dp[i][3];
        } else if (s[i + 1] == 'r') {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][1];
            dp[i+1][2] = dp[i][2] + a[i+1];
            dp[i+1][3] = min(dp[i][3], dp[i][2]);
        } else if (s[i + 1] == 'd') {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][1];
            dp[i+1][2] = dp[i][2];
            dp[i+1][3] = dp[i][3] + a[i+1];
        } else {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][1];
            dp[i+1][2] = dp[i][2];
            dp[i+1][3] = dp[i][3];
        }
    }

    ll ans = dp[N][0];
    for (i = 1; i <= 3; ++i) ans = min(ans, dp[N][i]);

    printf("%lld\n", ans);
    return 0;
}