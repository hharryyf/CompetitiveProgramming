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
typedef long double ld;

const ll mod = 998244353;
const int infint = 1030000000;
const ll infll = 1e18 + 17;

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

ll ex_euclidian(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = ex_euclidian(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll extented_crt(vector<ll> m , vector<ll> r){
    int n = m.size();
    ll MM = m[0] , R = r[0] , x , y , d;
    for(int i = 1; i < n; ++i){
        d = ex_euclidian(MM , m[i] , x , y);
        if((r[i] - R) % d)return -1;
        x = (r[i] - R) / d * x % (m[i] / d);
        R += x * MM;
        MM = MM / d * m[i];
        R %= MM;
    }
    return R > 0 ? R : R + MM;
}

/*
    xor(x, y) = pref[x] ^ pref[y] ^ a[LCA(x, y)]
*/

int f[MAX_SIZE];

set<int> st[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    if (st[fx].size() > st[fy].size()) swap(fx, fy);
    f[fx] = fy;
    for (auto v : st[fx]) {
        st[fy].insert(v);
    }
}

int ans = 0;
int a[MAX_SIZE], N, pre[MAX_SIZE];
vector<int> g[MAX_SIZE];

void dfs1(int v, int p) {
    pre[v] = pre[p] ^ a[v];
    for (auto nv : g[v]) {
        if (nv != p) {
            dfs1(nv, v);
        }
    }
}

void dfs2(int v, int p) {
    int s = find(v);
    st[s].insert(pre[v]);
    bool valid = true;
    for (auto nv : g[v]) {
        if (nv != p) {
            dfs2(nv, v);
        }
    }

    for (auto nv : g[v]) {
        if (nv != p) {
            int x = find(v), y = find(nv);
            if (st[x].size() > st[y].size()) {
                swap(x, y);
            }

            for (auto xx : st[x]) {
                if (st[y].find(xx ^ a[v]) != st[y].end()) {
                    valid = false;
                    break;
                }
            }

            unionset(x, y);

            if (!valid) break;
        }
    }

    if (!valid) {
        s = find(v);
        st[s].clear();
        ans++;
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        f[i] = i;
    }

    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    debug("here\n");
    dfs1(1, 0);
    debug("here\n");
    dfs2(1, 0);

    printf("%d\n", ans);
    return 0;
}