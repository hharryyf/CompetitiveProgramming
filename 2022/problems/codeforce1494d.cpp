#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1011
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

int wt[MAX_SIZE], f[MAX_SIZE];
int parent[MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
int N, K;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int main() {
    int i, j;
    scanf("%d", &N);
    K = N;
    for (i = 1; i < MAX_SIZE; ++i) f[i] = i;
    vector<array<int, 3>> edg;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%d", &a[i][j]);
            if (i != j) {
                edg.push_back({a[i][j], i, j});
            }
        }
    }

    sort(edg.begin(), edg.end());
    set<pair<int, int>> st;
    for (auto &e : edg) {
        int w = e[0], u = e[1], v = e[2];
        int fu = find(u), fv = find(v);
        if (wt[fu] == w && wt[fv] == w) continue;
        if (wt[fu] == w) {
            f[fv] = fu;
            st.insert(make_pair(fv, fu));
        } else if (wt[fv] == w) {
            f[fv] = fu;
            st.insert(make_pair(fv, fu));
        } else {
            ++K;
            f[fv] = f[fu] = K;
            wt[K] = w;
            st.insert(make_pair(fv, K));
            st.insert(make_pair(fu, K));
        }
    }

    for (i = 1; i <= N; ++i) {
        wt[i] = a[i][i];
    }

    printf("%d\n", K);
    for (i = 1; i <= K; ++i) {
        printf("%d ", wt[i]);
    }
    printf("\n");
    printf("%d\n", find(1));
    for (auto p : st) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}