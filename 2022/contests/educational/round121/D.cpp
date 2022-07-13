#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200022
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

int nxt[MAX_SIZE][19];
int pre[MAX_SIZE];
int up[MAX_SIZE];
int maxlog = 18;
int N;

int main() {
    int T;
    int i, j, k;
    up[0] = 1;
    for (i = 0; i <= 17; ++i) {
        for (j = (1 << i); j < min(MAX_SIZE, (1 << (i + 1))); ++j) {
            if (j == (1 << i)) {
                up[j] = (1 << i);
            } else {
                up[j] = (1 << (i + 1));
            }
        }
    }
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N + 4; ++i) {
            for (j = 0 ; j <= 18; ++j) {
                nxt[i][j] = -1;
            }

            pre[i] = 0;
        }

        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            ++v;
            pre[v]++;
        }

        for (i = 1; i <= N + 4; ++i) {
            pre[i] += pre[i-1];
        }

        for (j = 0; j <= maxlog; ++j) {
            for (i = 1, k = 0; i <= N + 4; ++i) {
                while (k < N + 4 && pre[k+1] - pre[i-1] <= (1 << j)) {
                    ++k;
                }

                nxt[i][j] = k;
                debug("nxt[%d][%d] = %d\n", i, j, nxt[i][j]);
            }
        }

        int ans = 1 << 25;
        for (i = 0; i <= maxlog; ++i) {
            for (j = 0 ; j <= maxlog; ++j) {
                int l = min(nxt[1][i], N + 1);
                int r = min(nxt[l + 1][j], N + 2);
                ans = min(ans, (1 << i) + (1 << j) + up[pre[N + 4] - pre[r]] - pre[N + 4]);
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}