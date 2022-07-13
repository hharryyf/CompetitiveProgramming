#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
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
const int inf32 = 1040000001;
const ll inf64 = 1e18 + 3;

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

vector<int> h[MAX_SIZE], g[MAX_SIZE];
int c[MAX_SIZE], p[MAX_SIZE], visited[MAX_SIZE], dp[MAX_SIZE];
int N;

void dfs(int v, int pre) {
    dp[v] = c[v];
    p[v] = pre;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            dp[v] += dp[nv];
        }
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &c[i]);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);
    
    for (i = 1; i <= N; ++i) {
        for (auto v : g[i]) {
            if (p[v] == i) {
                // i --> v
                if (dp[v] >= 2 || c[v] == 1) {
                    h[v].push_back(i);
                }

                if (c[i] == 1 || dp[1] - dp[v] >= 2) {
                    h[i].push_back(v);
                }
            }
        }
    }   

    queue<int> q;
    for (i = 1; i <= N; ++i) {
        if (c[i]) q.push(i);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (auto nv : h[v]) {
            if (!visited[nv]) {
                q.push(nv);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        printf("%d ", visited[i]);
    }

    printf("\n");
    return 0;
}