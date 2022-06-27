#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 72
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


const int inf = 1e8;
int N, M, K;
int a[MAX_SIZE][MAX_SIZE];
// (row, index, select number, mod)
int dp1[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int ans1[MAX_SIZE][MAX_SIZE];
int dp2[MAX_SIZE][MAX_SIZE];

void solve_1(int row) {
    int i, j, k;
    for (i = 0; i <= M; ++i) {
        for (k = 0 ; k <= M; ++k) {
            for (j = 0 ; j <= K; ++j) {
                dp1[i][k][j] = -inf;
            }
        }
    }

    for (i = 1 ; i < K; ++i) {
        ans1[row][i] = -inf;
    }

    dp1[0][0][0] = 0;

    for (k = 0; k < M; ++k) {
        for (i = 0; i <= M / 2; ++i) {
            for (j = 0; j < K; ++j) {
                dp1[k+1][i][j] = max(dp1[k+1][i][j], dp1[k][i][j]);
                dp1[k+1][i+1][(j + a[row][k+1]) % K] = max(dp1[k+1][i+1][(j + a[row][k+1]) % K], dp1[k][i][j] + a[row][k+1]);
            }
        }
    }

    for (i = 0; i < K; ++i) {
        for (j = 0 ; j <= M / 2; ++j) {
            for (k = 0 ; k <= M; ++k) {
                ans1[row][i] = max(ans1[row][i], dp1[k][j][i]);
            }
        }
    }
}

int main() {
    int i, j, k;
    scanf("%d%d%d", &N, &M, &K);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (i = 1; i <= N; ++i) {
        solve_1(i);
    }

    int ans = 0;
    for (i = 0; i <= N; ++i) {
        for (j = 0 ; j < K; ++j) {
            debug("%d ", ans1[i][j]);
            dp2[i][j] = -inf;
        }
        debug("\n");
    }

    dp2[0][0] = 0;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < K; ++j) {
            dp2[i+1][j] = max(dp2[i][j], dp2[i+1][j]);
            for (k = 0; k < K; ++k) {
                dp2[i+1][(j + k) % K] = max(dp2[i+1][(j + k) % K], dp2[i][j] + ans1[i+1][k]);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        ans = max(ans, dp2[i][0]);
    }

    printf("%d\n", ans);
    return 0;
}