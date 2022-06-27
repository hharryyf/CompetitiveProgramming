#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 5011
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

inline ll inv(ll x) {
    return qpow(x, mod - 2);
}

ll fac[23], ifac[23];
int N, M;

void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < 23; ++i) {
        fac[i] = mul(fac[i-1], i);
        ifac[i] = mul(ifac[i-1], inv(i));
    }
}

ll P(int n, int k) {
    return mul(fac[n], ifac[n-k]);
}

ll solve(vector<int> &cnt) {
    int i, curr = 0;
    ll tol = 1;
    for (i = 0 ; i < (int) cnt.size(); ++i) {
        if (cnt[i] == 0) continue;
        if (cnt[i] + curr > i) return 1;
        tol = mul(tol, P(i - curr, cnt[i]));
        curr = curr + cnt[i];
    }

    for (auto v : cnt) {
        debug("%d ", v);
    } 
    debug("\n total=%lld\n", tol);
    return mul(fac[N] - tol, ifac[N]);
}

int d[22][50011];

int main() {
    int i, j;
    init();
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &d[i][j]);
        }
    }

    ll ans = 0;
    for (i = 1; i <= M; ++i) {
        vector<int> cnt(N+1);
        for (j = 1; j <= N; ++j) {
            cnt[d[j][i]-1]++;
        }
        debug("solve %d: \n", i); 
        ans = add(ans, solve(cnt));
    }

    printf("%lld\n", ans);
    return 0;
}