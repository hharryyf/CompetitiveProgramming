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

int dp[MAX_SIZE];

vector<int> g[MAX_SIZE];

void dfs(int v, int pre) {
    dp[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
            if (dp[nv] != 0) {
                dp[v] = 0;
            }
        }
    }
}

int main() {
    int i, T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            dp[i] = -1;
            g[i].clear();
        }

        for (i = 1; i < N; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(1, 0);

        int cnt = 0, bud = 0;
        for (i = 2; i <= N; ++i) {
            if (dp[i] == 0) {
                bud++;
            } else {
                cnt++;
            }
        }

        int ans = cnt - bud + 1;
        for (auto v : g[1]) {
            if (dp[v]) {
                ans--;
                break;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}