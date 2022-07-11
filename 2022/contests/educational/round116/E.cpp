#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 511
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

int N, X;
ll dp[MAX_SIZE][MAX_SIZE];
ll C[MAX_SIZE][MAX_SIZE];
ll pw[MAX_SIZE][MAX_SIZE];

int main() {
    cin >> N >> X;
    int i, j, k;
    for (i = 0; i < MAX_SIZE; ++i) {
        C[i][0] = 1;
    }
    
    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 1; j <= i; ++j) {
            C[i][j] = add(C[i-1][j], C[i-1][j-1]);
        }
    }

    for (i = 0; i <= X; ++i) dp[i][0] = 1;
    
    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 0; j < MAX_SIZE; ++j) {
            pw[i][j] = qpow(i, j);
        }
    }

    for (i = 1; i <= X; ++i) {
        for (j = 1; j <= N; ++j) {
            int pre = max(0, i - (j - 1));
            int loss = i - pre;
            if (pre != i) {
                for (k = 0; k <= j; ++k) {
                    dp[i][j] = add(dp[i][j], mul(dp[pre][k], mul(pw[loss][j - k], C[j][j-k])));
                }
            }
        }
    }

    cout << dp[X][N] << endl;
    return 0;
}