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

int M, N;

vector<int> disc, tmp;
int f[MAX_SIZE];
multiset<int> ans[MAX_SIZE];
multiset<int> g[MAX_SIZE];
vector<int> input[MAX_SIZE];
vector<pair<int, int>> ret;
vector<vector<pair<int, int>>> retall;

int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int aa = find(x), bb = find(y);
    f[aa] = bb;
}

void preprocess() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    disc.push_back(0);
}

void euler(int v) {
    while (!g[v].empty()) {
        int nv = *g[v].begin();
        g[nv].erase(g[nv].find(v));
        g[v].erase(g[v].find(nv));
        euler(nv);
        ret.emplace_back(v, nv);
    }
}

int deg[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &M);
    preprocess();
    for (int i = 1; i <= M; ++i) {
        int n;
        scanf("%d", &n);
        while (n--) {
            int v;
            scanf("%d", &v);
            tmp.push_back(v);
            input[i].push_back(v);
        }
    }   

    sort(tmp.begin(), tmp.end());

    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    N = (int) disc.size() - 1;
    for (i = 1; i <= M; ++i) {
        for (auto v : input[i]) {
            int idx = lower_bound(disc.begin(), disc.end(), v) - disc.begin();
            deg[i] ^= 1;
            deg[idx + M] ^= 1;
            unionset(i, idx + M);
            g[i].insert(idx + M);
            g[idx + M].insert(i);
        }
    }

    for (i = 1; i <= N + M; ++i) {
        if (deg[i]) {
            printf("NO\n");
            return 0;
        }
    }

    for (i = 1; i <= N + M; ++i) {
        if (find(i) == i) {
            euler(i);
            reverse(ret.begin(), ret.end());
            retall.push_back(ret);
            ret.clear();
        }
    }

    for (auto vc : retall) {
        debug("print cycle\n");
        for (auto p : vc) {
            debug("%d --> %d\n", p.first, p.second);
            if (p.first > M) {
                ans[p.second].insert(-disc[p.first - M]);
            } else {
                ans[p.first].insert(disc[p.second - M]);
            }
        }
    }

    printf("YES\n");
    for (i = 1; i <= M; ++i) {
        for (auto v : input[i]) {
            if (ans[i].find(v) != ans[i].end()) {
                ans[i].erase(ans[i].find(v));
                printf("R");
            } else {
                ans[i].erase(ans[i].find(-v));
                printf("L");
            }
        }
        printf("\n");
    }
    return 0;
}