#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 4011
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

bool dp[MAX_SIZE][MAX_SIZE];
int N, a[MAX_SIZE];

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N * 2; ++i) {
            scanf("%d", &a[i]);
            for (j = 0; j <= 2 * N; ++j) {
                dp[i][j] = false;
            }
        }

        vector<int> stk;

        for (i = 1; i <= N * 2; ++i) {
            if (stk.empty()) {
                stk.push_back(i);
            } else {
                if (a[stk.back()] < a[i]) stk.push_back(i);
            }
        }

        vector<int> sz;

       

        for (i = 1; i < (int) stk.size(); ++i) {
            sz.push_back(stk[i] - stk[i-1]);
        }

        sz.push_back(N * 2 + 1 - stk.back());


         for (auto v : sz)  {
            debug("%d ", v);
        }
        debug("\n");

        int M = sz.size();

        for (i = 0 ; i <= M; ++i) dp[i][0] = true;

        for (i = 0; i < M; ++i) {
            for (j = 0 ; j <= 2 * N; ++j) {

                if (dp[i][j]) {
                    if (j + sz[i] <= 2 * N) {
                        dp[i+1][j+sz[i]] = true;
                    }
                    dp[i+1][j] = true;
                }
            }
        }

        printf("%s\n", dp[M][N] ? "YES" : "NO");
    }
    return 0;
}