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

vector<int> g[MAX_SIZE];

ll fac[MAX_SIZE];
ll dp[MAX_SIZE];
int N;

ll dfs(int v, int pre) {
    dp[v] = 1;
    int cnt = 0;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dp[v] = mul(dp[v], dfs(nv, v));
            cnt++;
        }
    }

    if (v == 1) {
        dp[v] = mul(dp[v], fac[cnt]);
    } else {
        dp[v] = mul(dp[v], fac[cnt + 1]);
    }
    return dp[v];
}

int main() {
    int i;
    scanf("%d", &N);
    fac[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) fac[i] = mul(fac[i-1], i);

    for (i = 0 ; i < N - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    } 

    dp[1] = dfs(1, 0);
    printf("%lld\n", mul(dp[1], N));
    return 0;
}