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
int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

pair<int, int> q[MAX_SIZE];
int cnt[MAX_SIZE], height[MAX_SIZE], p[MAX_SIZE];
int N, M, Q;

void dfs(int v, int pre) {
    height[v] = height[pre] + 1;
    p[v] = pre;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}

void create(int u, int v) {
    debug("construct path from %d to %d\n", u, v);
    vector<int> l, r, res;
    bool rev = false;
    if (height[u] < height[v]) {
        swap(u, v);
        rev = true;
    } 

    while (height[u] != height[v]) {
        l.push_back(u);
        u = p[u];
    }

    while (u != v) {
        l.push_back(u);
        r.push_back(v);
        u = p[u], v = p[v];
    } 

    l.push_back(u);
    reverse(r.begin(), r.end());
    for (auto vv : r) l.push_back(vv);
    if (rev) {
        reverse(l.begin(), l.end());
    }

    printf("%d\n", (int) l.size());
    for (auto vv : l) {
        printf("%d ", vv);
    }
    printf("\n");
}

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        f[i] = i;
    }

    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (find(u) != find(v)) {
            g[u].push_back(v);
            g[v].push_back(u);
            unionset(u, v);
        }
    }

    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        scanf("%d%d", &q[i].first, &q[i].second);
        cnt[q[i].first]++;
        cnt[q[i].second]++;
    }

    int tol = 0;
    for (i = 1; i <= N; ++i) {
        tol += (cnt[i] & 1);
    }

    if (tol != 0) {
        printf("NO\n%d\n", tol / 2);
        return 0;
    }

    printf("YES\n");
    
    debug("start dfs\n");
    dfs(1, 0);
    debug("end dfs\n");

    for (i = 1; i <= Q; ++i) {
        create(q[i].first, q[i].second);
    }

    return 0;
}