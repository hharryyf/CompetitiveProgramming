#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 102
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

const ll mod = 1000000007;

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

vector<int> g[MAX_SIZE];
int tol, N, K;
vector<int> cand;

void dfs(int v, int pre, int d, int td, int c) {
    if (td == d) tol++;
    for (auto nv : g[v]) {
        if (nv  != pre) {
            dfs(nv, v, d + 1, td, c);
            if (v == c) {
                if (tol != 0) {
                    cand.push_back(tol);                
                    tol = 0;
                }
            }
        }
    }
}

int dp[MAX_SIZE][MAX_SIZE];

int main() {
    int i, j, k;
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &K);
        assert(K >= 2);
        for (i = 1; i <= N; ++i) {
            g[i].clear();
        }

        for (i = 1; i < N; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        if (K == 2) {
            printf("%lld\n", 1ll * N * (N - 1) / 2);
        } else {
            ll ans = 0;
            for (i = 1; i <= N; ++i) {
                for (j = 2; j <= N; j = j + 2) {
                    tol = 0;
                    cand.clear();
                    cand.push_back(0);
                    dfs(i, 0, 0, j / 2, i);
                    int sz = (int) cand.size() - 1;
                    // dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * cand[i]                    
                    memset(dp, 0, sizeof(dp));
                    dp[0][0] = 1;
                    debug("dist=%d center = %d\n", j, i);
                    for (auto v : cand) {
                        debug("%d ", v);
                    }
                    debug("\n");
                    for (int v = 1; v <= sz; ++v) {
                        for (k = 0; k <= K; ++k) {
                            dp[v][k] = add(dp[v-1][k], k == 0 ? 0 : mul(dp[v-1][k-1], cand[v]));
                            debug("dp[%d][%d] = %d\n", v, k, dp[v][k]);
                        }
                    }

                    ans = add(ans, dp[sz][K]);
                }
            }
            
            printf("%lld\n", ans);
        }
    }
    return 0;
}