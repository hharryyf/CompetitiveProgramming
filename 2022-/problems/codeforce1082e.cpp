#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 500011
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

vector<int> val[MAX_SIZE];
int pre[MAX_SIZE];
int lst[MAX_SIZE];
int N, C;

int main() {
    int i, mx = 0;
    scanf("%d%d", &N, &C);
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        pre[i] = pre[i-1];
        mx = max(mx, v);
        if (v == C) {
            pre[i]++;
        } else {
            if (lst[v] == 0) {
                val[v].push_back(1);
            } else {
                val[v].push_back(-pre[i] + pre[lst[v] - 1]);
                val[v].push_back(1);      
            }
            lst[v] = i;
        }
    }

    int curr = 0;
    for (i = 1; i <= mx; ++i) {
        if (i == C) continue;
        int sm = 0, res = 0;
        debug("show vector for %d\n", i);
        for (auto v : val[i]) {
            debug("%d ", v);
            sm += v;
            if (sm < 0) {
                sm = 0;
            } else {
                res = max(sm, res);
            }
        }
        debug("\n");
        curr = max(curr, res);
    }

    printf("%d\n", pre[N] + curr);
    return 0;
}