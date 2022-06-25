#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 211
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

int N;
ll dp[MAX_SIZE][MAX_SIZE];
int pos[MAX_SIZE][MAX_SIZE];
ll pre[MAX_SIZE][MAX_SIZE];
ll c[MAX_SIZE][MAX_SIZE];
int parent[MAX_SIZE];

ll query(int x1, int y1, int x2, int y2) {
    return pre[x2][y2] + pre[x1-1][y1-1] -  pre[x1-1][y2] - pre[x2][y1-1];
}

ll cost(int l, int r) {
    if (l > r) return 0;
    debug("cost <%d,%d> = %lld\n", l, r, query(l, 1, r, N) - query(l, l, r, r));
    return query(l, 1, r, N) - query(l, l, r, r);
}

ll f(int l, int r) {
    if (l > r) return 0;
    if (l == r) {
        pos[l][r] = l;
        return 0;
    }
    if (dp[l][r] != -1) return dp[l][r];
    int i, best = 0;
    ll ret = 1e18;
    for (i = l; i <= r; ++i) {
        ll curr = f(l, i - 1) + f(i + 1, r) + cost(l, i - 1) + cost(i + 1, r);
        if (ret > curr) {
            ret = curr;
            best = i;
        }
    }

    pos[l][r] = best;
    return dp[l][r] = ret;
}

int dfs(int l, int r) {
    if (l > r) return 0;
    int L = dfs(l, pos[l][r] - 1), R = dfs(pos[l][r] + 1, r);
    if (L != 0) {
        parent[L] = pos[l][r];
    }

    if (R != 0) {
        parent[R] = pos[l][r];
    }

    return pos[l][r];
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 0; i <= N; ++i) {
        for (j = 0; j <= N; ++j) {
            dp[i][j] = -1;
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%lld", &c[i][j]);
            pre[i][j] = c[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }

    ll ret = f(1, N);

    debug("%lld\n", ret);
    
    dfs(1, N);

    for (i = 1; i <= N; ++i) {
        printf("%d ", parent[i]);
    }    

    printf("\n");
    return 0;
}