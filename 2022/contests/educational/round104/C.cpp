#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
#define MAX_SIZE 524312
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

int N;
vector<pair<int, int>> ret;
multiset<int> g[101];
int ans[101][101];
void euler(int v) {
    while (!g[v].empty()) {
        int nv = *g[v].begin();
        g[nv].erase(g[nv].find(v));
        g[v].erase(g[v].find(nv));
        euler(nv);
        ret.emplace_back(v, nv);
    }
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);

        ret.clear();
        for (i = 1; i <= N; ++i) {
            g[i].clear();
        }

        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                ans[i][j] = 2;
            }
        }

        if (N % 2 == 0) {
            for (i = 1; i <= N - 1; i = i + 2) {
                ans[i][i+1] = ans[i+1][i] = 0;
            }
        }

        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                if (ans[i][j] == 2) {
                    g[i].insert(j);
                    g[j].insert(i);
                }
            }
        }

        euler(1);

        reverse(ret.begin(), ret.end());

        for (auto p : ret) {
            ans[p.first][p.second] = 1;
            ans[p.second][p.first] = -1;
        }

        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                printf("%d ", ans[i][j]);
            }
        }

        printf("\n");
    }
    return 0;
}