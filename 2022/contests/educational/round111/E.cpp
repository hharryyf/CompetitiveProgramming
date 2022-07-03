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

char s[MAX_SIZE];
int dp[(1 << 17) + 11];
int qlen[MAX_SIZE][17];
int N, K;

int query(int l, int dim) {
    if (l > N) return N + 1;
    return qlen[l][dim];
}    

bool check(int mid) {
    int i, j;
    debug("check %d\n", mid);
    for (j = 0 ; j < K; ++j) {
        for (i = 1; i <= N + 1; ++i) {
            qlen[i][j] = N + 1;
        }
    }

    debug("finish precompute\n");
    for (j = 0 ; j < K; ++j) {
        int curr = 0;
        for (i = N; i >= 1; --i) {
            if (s[i] == 'a' + j || s[i] == '?') {
                curr++;
            } else {
                curr = 0;
            }

            if (curr >= mid) {
                qlen[i][j] = i + mid - 1;
            } else {
                qlen[i][j] = qlen[i+1][j];
            }
        }        
    }
    
    debug("finish precompute 2\n");

    for (j = 0 ; j < K; ++j) {
        for (i = 1; i <= N; ++i) {
            debug("qlen[%d][%d] = %d\n", i, j, qlen[i][j]);
        }
    }

    dp[0] = 0;
    for (i = 1; i < (1 << K); ++i) dp[i] = N + 1;
    for (i = 0; i < (1 << K); ++i) {
        for (j = 0 ; j < K; ++j) {
            if ((i >> j) & 1) {
                int p = i ^ (1 << j);
                dp[i] = min(dp[i], query(dp[p] + 1, j));
            }
        }
    }
    debug("finish check %d\n", mid);
    return dp[(1 << K) - 1] <= N;
}

int main() {
    scanf("%d%d", &N, &K);
    scanf("%s", s + 1);

    int low = 0, high = N, ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}