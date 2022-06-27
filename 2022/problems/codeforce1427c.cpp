#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

struct position {
    int x, y, t;
};

int N;
position pos[MAX_SIZE];
int dp[MAX_SIZE], mx[MAX_SIZE];

int main() {
    int i, r, j;
    scanf("%d%d", &r, &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d%d", &pos[i].t, &pos[i].x, &pos[i].y);
        dp[i] = mx[i] = -10000000;
    }

    pos[0].x = pos[0].y = 1;

    for (i = 1; i <= N; ++i) {
        int idx = i - 1;
        for (j = i - 1; j >= 0 && pos[i].t - pos[j].t < 2 * r; --j) {
            if ((pos[i].t - pos[j].t) >= (abs(pos[i].x - pos[j].x) + abs(pos[i].y - pos[j].y))) {
                dp[i] = max(dp[i], dp[j] + 1);
                debug("transite from state %d to %d\n", j, i);
            }

            idx = j;
        }

        for (j = idx; j >= 0; --j) {
            if (pos[i].t - pos[j].t >= 2 * r) {
                dp[i] = max(dp[i], mx[j] + 1);
                break;
            }
        }

        mx[i] = max(dp[i], mx[i-1]);

        debug("dp[%d] = %d\n", i, dp[i]);
    }

    printf("%d\n", mx[N]);
    return 0;
}