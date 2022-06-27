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

vector<int> g[MAX_SIZE];
int height[MAX_SIZE];
int N;
int parent[MAX_SIZE][18];

void dfs(int u, int pre, bool setp=false) {
    height[u] = height[pre] + 1;

    if (setp) parent[u][0] = pre;

    for (auto nv : g[u]) {
        if (nv != pre) {
            dfs(nv, u, setp);
        }
    }
}

int LCA(int u, int v) {
    int i;
    if (height[u] < height[v]) swap(u, v);
    for (i = 17; i >= 0; --i) {
        if (height[u] >= height[v] + (1 << i)) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (i = 17; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    } 

    return parent[u][0];
}

int dist(int u, int v) {
    debug("dist(%d,%d) = %d\n", u, v, height[u] + height[v] - 2 * height[LCA(u, v)]);
    return height[u] + height[v] - 2 * height[LCA(u, v)];
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    int pivot = 1;
    for (i = 1; i <= N; ++i) {
        if (height[i] > height[pivot]) pivot = i;
    }

    memset(height, 0, sizeof(height));

    dfs(pivot, 0, true);

    for (int j = 1; j <= 17; ++j) {
        for (i = 1; i <= N; ++i) {
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }

    int pivot2 = 1;
    for (i = 1; i <= N; ++i) {
        if (height[i] > height[pivot2]) pivot2 = i;
    }
    
    int pivot3 = 0;
    for (i = 1; i <= N; ++i) {
        if (i == pivot || i == pivot2) continue;
        if (pivot3 == 0) {
            pivot3 = i;
        } else {
            int d = dist(i, pivot) + dist(pivot, pivot2) + dist(pivot2, i);
            if (d > dist(pivot3, pivot) + dist(pivot, pivot2) + dist(pivot2, pivot3)) {
                pivot3 = i;
            }
        }
    }

    printf("%d\n", (dist(pivot3, pivot) + dist(pivot, pivot2) + dist(pivot2, pivot3)) / 2);
    printf("%d %d %d\n", pivot, pivot2, pivot3);
    return 0;
}
