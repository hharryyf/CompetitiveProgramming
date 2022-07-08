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

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, M, K, Q, i;
        set<int> st;
        map<int, int> row, col;
        scanf("%d%d%d%d", &N, &M, &K, &Q);
        for (i = 1; i <= Q; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            row[x] = i;
            col[y] = i;
        }

        int mn = Q + 1;
        if ((int) col.size() == M) {
            for (auto c : col) {
                mn = min(c.second, mn);
            }
        }

        debug("mn = %d\n", mn);

        for (auto x : row) {
            debug("has %d %d --> mn = %d\n", x.first, x.second, mn);
            if (x.second >= mn || mn == Q + 1) st.insert(x.second);
        }

        mn = Q + 1;

        if ((int) row.size() == N) {
            for (auto c : row) {
                mn = min(c.second, mn);
            }
        }

        debug("mn = %d\n", mn);
        for (auto x : col) {
            debug("has %d %d --> mn = %d\n", x.first, x.second, mn);
            if (x.second >= mn || mn == Q + 1) st.insert(x.second);
            else {
                debug("fail %d %d\n", x.first, x.second);
            }
        }

        for (auto v : st) {
            debug("%d ", v);
        }
        debug("\n");

        printf("%lld\n", qpow(K, (ll) st.size()));
    }
    return 0;
}
