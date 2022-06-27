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

// dp[i][j] means a moves i steps while b moves j steps
// what's the probability that a moves to the root quicker than b
ll dp[MAX_SIZE][MAX_SIZE];

int N;

vector<int> g[MAX_SIZE];
int parent[MAX_SIZE][9], height[MAX_SIZE];
ll ans = 0;

void dfs(int v, int pre) {
    parent[v][0] = pre;
    height[v] = height[pre] + 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}

int LCA(int u, int v) {
    int i;
    if (height[u] < height[v]) swap(u, v);
    for (i = 8; i >= 0; i--) {
   	   if (height[u] >= (1 << i) + height[v]) {
	   	  u = parent[u][i];	  
	   }
   }
   
   if (u == v) return u;
   
   for (i = 8; i >= 0; i--) {
   	   if (parent[u][i] != parent[v][i]) {
			 u = parent[u][i];
			 v = parent[v][i];	  
	   }
   }
   
   return parent[u][0];
}

void solve(int root) {
    for (int i = 1; i <= N; ++i) height[i] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0 ; j <= 8; ++j) {
            parent[i][j] = 0;
        }
    }

    dfs(root, 0);
    
    for (int j = 1; j < 9; ++j) {
        for (int i = 1; i <= N; ++i) {
            parent[i][j] = parent[parent[i][j-1]][j-1];        
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j < i; ++j) {
            int lca = LCA(i, j);
            debug("root is %d, LCA(%d,%d)=%d\n", root, i, j, lca);
            debug("height = %d %d\n", height[i], height[j]);
            ans = add(ans, dp[height[i] - height[lca]][height[j] - height[lca]]);
        }
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 1; i <= N; ++i) {
        dp[0][i] = 1;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            dp[i][j] = add(dp[i-1][j], dp[i][j-1]);
            dp[i][j] = mul(dp[i][j], qpow(2, mod - 2));
        }
    }

    for (int i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) {
        solve(i);
    }

    cout << mul(ans, qpow(N, mod - 2)) << endl;
    return 0;
}