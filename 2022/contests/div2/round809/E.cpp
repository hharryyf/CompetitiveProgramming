#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
#define MAX_LOG 19
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

int logs[MAX_SIZE];

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int a[MAX_SIZE];
int rid[MAX_SIZE];
struct ST {
    
    int table[MAX_LOG][MAX_SIZE];
    int n;
    int tp;

    int RMQ(int l, int r) {
        if (l > r) return 4 * MAX_SIZE * (tp ? 1 : -1);
        int len = r - l + 1;
        if (tp) {
            return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        } else {
            return max(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        }
    }

    void build() {
        int i, j;
        for (i = 1; i <= n; i++) {
            table[0][i] = a[i];
        }
        
        for (i = 1; i < MAX_LOG; i++) {
            int prel = (1 << (i - 1));
            for (j = 1; j <= n; j++) {
                if (j + prel <= n) {
                    if (tp) {
                        table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
                    } else {
                        table[i][j] = max(table[i-1][j], table[i-1][j+prel]);
                    }
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }
};

ST mn, mx;

int N, M, Q;
int parent[MAX_SIZE][MAX_LOG];
vector<int> g[MAX_SIZE];
int f[MAX_SIZE], wt[MAX_SIZE], height[MAX_SIZE];
int cnt = 0, cid = 0;
int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}


int LCA(int u, int v) {
    if (height[u] < height[v]) swap(u, v);
    int i;
    for (i = 18; i >= 0; --i) {
        if (height[u] - height[v] >= (1 << i)) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;
    for (i = 18; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

void dfs(int v, int d=0) {
    if (a[v] != 0) return;
    a[v] = ++cid;
    rid[cid] = v;
    height[v] = d;
    for (auto nv : g[v]) {
        dfs(nv, d + 1);
    }
}

int main() {
    int T;
    precompute();
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        mn.tp = 1;
        mx.tp = 0;
        scanf("%d%d%d", &N, &M, &Q);
        mn.n = mx.n = N;
        cid = 0;
        for (i = 1; i <= N * 2; ++i) {
            g[i].clear();
            height[i] = 0;
            a[i] = rid[i] = 0;
            f[i] = i;
            wt[i] = 0;
            for (j = 0 ; j < MAX_LOG; ++j) {
                parent[i][j] = 0;
            }
        }

        cnt = N;
        for (i = 1; i <= M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            int fx = find(u), fy = find(v);
            if (fx != fy) {
                ++cnt;
                f[fx] = cnt;
                f[fy] = cnt;
                wt[cnt] = i;
                parent[fx][0] = parent[fy][0] = cnt;
                g[cnt].push_back(fx);
                g[cnt].push_back(fy);
            }
        }

        dfs(cnt);
        for (j = 1; j <= 18; ++j) {
            for (i = 1; i <= cnt; ++i) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }

        for (i = 1; i <= N; ++i) {
            debug("dfsorder[%d] = %d\n", i, a[i]);
        }
        mn.build();
        mx.build();

        while (Q-- > 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            int d1 = rid[mn.RMQ(l, r)], d2 = rid[mx.RMQ(l, r)];
            
            printf("%d ", wt[LCA(d1, d2)]);
        }

        printf("\n");
    }
    return 0;
}