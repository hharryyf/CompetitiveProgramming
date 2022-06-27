#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200011
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

vector<int> g[MAX_SIZE], g2[MAX_SIZE];
int visited[MAX_SIZE], color[MAX_SIZE];
array<int, 3> c[MAX_SIZE];
vector<int> ord;

int N, M;
bool valid = true;

void coloring(int v) {
    for (auto nv : g2[v]) {
        if (color[nv] == -1) {
            color[nv] = color[v] ^ 1;
            coloring(nv);
        } else if ((color[nv] ^ color[v]) == 0) {
            valid = false;
        }
    }
}

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        }

        if (visited[nv] == 1) {
            valid = false;
        }
    }
    visited[v] = 2;
    ord.push_back(v);
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d", &c[i][0], &c[i][1], &c[i][2]);
        g2[c[i][1]].push_back(c[i][2]);
        g2[c[i][2]].push_back(c[i][1]);
    }

    for (i = 1; i <= N; ++i) color[i] = -1;

    for (i = 1; i <= N; ++i) {
        if (color[i] == -1) {
            color[i] = 0;
            coloring(i);
        }
    }

    if (!valid) {
        debug("not bipartite\n");
        printf("NO\n");
        return 0;
    }

    for (i = 1; i <= N; ++i) {
        debug("color[%d] = %d\n", i, color[i]);
    }

    for (i = 1; i <= M; ++i) {
        if (color[c[i][1]]) swap(c[i][1], c[i][2]);
        if (c[i][0] == 1) {
            g[c[i][1]].push_back(c[i][2]);
            debug("add edge <%d, %d>\n", c[i][1], c[i][2]);
        } else {
            g[c[i][2]].push_back(c[i][1]);
            debug("add edge <%d, %d>\n", c[i][2], c[i][1]);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) {
            valid = true;
            dfs(i);
            if (!valid) {
                printf("NO\n");
                debug("has cycle");
                return 0;
            }
        }
    }

    reverse(ord.begin(), ord.end());

    for (i = 0 ; i < (int) ord.size(); ++i) {
        visited[ord[i]] = i;
    }

    printf("YES\n");
    for (i = 1; i <= N; ++i) {
        printf("%c %d\n", (color[i] == 0) ? 'L' : 'R', visited[i]);
    }
    return 0;
}