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

int f[MAX_SIZE];
vector<int> comp[MAX_SIZE];
vector<pair<int, int>> g[MAX_SIZE];
int a[MAX_SIZE], dist[MAX_SIZE];
int p[MAX_SIZE << 3];
int N, Q, s, d;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (comp[fx].size() > comp[fy].size()) swap(fx, fy);
    f[fx] = fy;
    for (auto v : comp[fx]) comp[fy].push_back(v);
    comp[fx].clear();
}

void dfs(int v, int pre, int dd) {
    dist[v] = dd;
    for (auto np : g[v]) {
        if (np.first != pre) {
            dfs(np.first, v, max(dd, np.second));
        }
    }
}

int main() {
    int i, cnt = 0;
    scanf("%d%d%d%d", &N, &Q, &s, &d);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
        f[i] = i;
        comp[i].push_back(i);
        cnt++;
    }

    set<int> pos(a + 1, a + 1 + N);
    
    while (cnt > 1) {
        vector<array<int, 3>> edge;
        for (i = 1; i <= N; ++i) {
            if (find(i) == i) {
                array<int, 3> ne = {-1, -1, 100000000};

                for (auto v : comp[i]) {
                    pos.erase(a[v]);
                }

                for (auto v : comp[i]) {
                    // a[v] - d
                    auto it = pos.lower_bound(a[v] - d);
                    if (it != pos.end()) {
                        if (ne[0] == -1 || ne[2] > abs(d - abs(a[v] - *it))) {
                            ne = {v, p[*it], abs(d - abs(a[v] - *it))};
                        }
                    }

                    if (it != pos.begin()) {
                        it = prev(it);
                        if (ne[0] == -1 || ne[2] > abs(d - abs(a[v] - *it))) {
                            ne = {v, p[*it], abs(d - abs(a[v] - *it))};
                        }
                    }
                    // a[v] + d
                    it = pos.lower_bound(a[v] + d);
                    if (it != pos.end()) {
                        if (ne[0] == -1 || ne[2] > abs(d - abs(a[v] - *it))) {
                            ne = {v, p[*it], abs(d - abs(a[v] - *it))};
                        }
                    }

                    if (it != pos.begin()) {
                        it = prev(it);
                        if (ne[0] == -1 || ne[2] > abs(d - abs(a[v] - *it))) {
                            ne = {v, p[*it], abs(d - abs(a[v] - *it))};
                        }
                    }
                }

                for (auto v : comp[i]) {
                    pos.insert(a[v]);
                }

                if (ne[0] != -1) {
                    edge.push_back(ne);
                }
            }
        }

        for (auto e : edge) {
            if (find(e[0]) != find(e[1])) {
                unionset(e[0], e[1]);
                g[e[0]].emplace_back(e[1], e[2]);
                g[e[1]].emplace_back(e[0], e[2]);
                cnt--;
            }
        }
    }

    dfs(s, 0, 0);

    while (Q-- > 0) {
        int v, k;
        scanf("%d%d", &v, &k);
        printf("%s\n", dist[v] <= k ? "YES" : "NO");
    }
    return 0;
}