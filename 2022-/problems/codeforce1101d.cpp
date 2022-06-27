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
int a[MAX_SIZE];
vector<int> prime[MAX_SIZE];
int visited[MAX_SIZE];
int dist[MAX_SIZE];
int N;

vector<int> vc[MAX_SIZE];

vector<int> vis;
void dfs(int v, int pre, int pri) {
    vis.push_back(v);
    dist[v] = dist[pre] + 1;
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            if (binary_search(vc[pri].begin(), vc[pri].end(), nv)) {
                dfs(nv, v, pri);
            }
        }
    }
}

int solve(int p) {
    int ret = 0;
    debug("solve for %d\n", p);
    for (auto v : vc[p]) {
        visited[v] = 0;
        dist[v] = 0;
    }

    for (auto v : vc[p]) {
        if (!visited[v]) {
            debug("start dfs from vertex %d\n", v);
            vis.clear();
            int d = 0;
            dfs(v, 0, p);
            for (auto nv : vis) {
                debug("%d-->", nv);
            }
            debug("\n");
            for (auto nv : vis) {
                if (dist[d] <= dist[nv]) d = nv;
            }

            for (auto nv : vis) {
                visited[nv] = 0;
                dist[nv] = 0;
            }

            vis.clear();
            debug("next start %d\n", d);
            dfs(d, 0, p);
            for (auto nv : vis) {
                ret = max(ret, dist[nv]);    
            }
        }
    }

    return ret;
}

int main() {
    int i, j, ans = 0;
    for (i = 2; i < MAX_SIZE; ++i) {
        if (!visited[i]) {
            for (j = 1; j * i < MAX_SIZE; ++j) {
                visited[i * j] = 1;
                prime[i * j].push_back(i);
            }
        }
    }
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i < N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (i = 1; i <= N; ++i) {
        for (auto v : prime[a[i]]) {
            vc[v].push_back(i);
        }
    }

    memset(visited, 0, sizeof(visited));

    for (i = 2; i <= 200000; ++i) {
        if (!vc[i].empty()) {
            ans = max(ans, solve(i));
        }
    }   

    printf("%d\n", ans);
    return 0;
}