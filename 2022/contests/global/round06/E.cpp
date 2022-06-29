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

int N;
ll ans = 0;
int a[MAX_SIZE];
int d[MAX_SIZE];
map<pair<int, int>, int> mp;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        ans += a[i];
    }

    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int s, t, u;
        scanf("%d%d%d", &s, &t, &u);
        if (mp.find(make_pair(s, t)) != mp.end()) {
            int cu = mp[make_pair(s, t)];
            int curr = max(a[cu] - d[cu], 0);
            d[cu]--;
            int nxt = max(a[cu] - d[cu], 0);
            ans = ans + nxt - curr;
            mp.erase(make_pair(s, t));
            if (u != 0) {
                mp[make_pair(s, t)] = u;
                curr = max(0, a[u] - d[u]);
                d[u]++;
                nxt = max(0, a[u] - d[u]);
                ans = ans + nxt - curr;  
            } 
        } else {
            mp[make_pair(s, t)] = u;
            int curr = max(0, a[u] - d[u]);
            d[u]++;
            int nxt = max(0, a[u] - d[u]);
            ans = ans + nxt - curr;
        }

        printf("%lld\n", ans);
    }
    return 0;
}