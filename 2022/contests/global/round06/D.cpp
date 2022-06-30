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

struct rela {
    int a, b;
    ll v;
};


ll a[MAX_SIZE];
queue<int> q1, q2;

int main() {
    int i, N, M;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        a[u] += w;
        a[v] -= w;
    }

    for (i = 1; i <= N; ++i) {
        if (a[i] > 0) {
            q1.push(i);
        } else if (a[i] < 0) {
            q2.push(i);
        }
    }

    vector<rela> ret;
    while (!q1.empty() && !q2.empty()) {
        auto a1 = q1.front(), b1 = q2.front();
        ll mn = min(a[a1], -a[b1]);
        ret.push_back({a1, b1, mn});
        a[a1] -= mn;
        a[b1] += mn;
        if (!a[a1]) q1.pop();
        if (!a[b1]) q2.pop();
    }

    printf("%d\n", (int) ret.size());
    for (auto v : ret) {
        printf("%d %d %lld\n", v.a, v.b, v.v);
    }
    return 0;
}