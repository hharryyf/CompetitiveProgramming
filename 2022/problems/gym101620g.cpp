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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef long double ld;

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
ld dist[MAX_SIZE], sm[MAX_SIZE];
int deg[MAX_SIZE], small[MAX_SIZE];
int N, M;


struct node {
    int v;
    ld d;
    node(int v, ld d) : v(v), d(d) {}

    bool operator < (node other) const {
        return d > other.d;
    }
};

int visited[MAX_SIZE];
priority_queue<node> q;

int main() {
    int i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }

    for (i = 1; i < N; ++i) {
        dist[i] = 1e17;
    }

    q.push(node(N, 0));

    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        if (visited[curr.v]) continue;
        visited[curr.v] = 1;
        for (auto nv : g[curr.v]) {
            ++small[nv];
            sm[nv] += dist[curr.v];
            if (dist[nv] >= (sm[nv] + deg[nv]) / small[nv]) {
                dist[nv] = (sm[nv] + deg[nv]) / small[nv];
                q.push(node(nv, dist[nv]));
            }

        }
    }

    printf("%.12Lf\n", dist[1]);
    return 0;
}