#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 5243121
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

int visited[MAX_SIZE];
int occ[MAX_SIZE];
int dp[MAX_SIZE];

int main () {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, N, M, mn, mx;
        scanf("%d%d", &N, &M);
        mn = M, mx = 0;
        for (i = 0 ; i <= M; ++i) {
            occ[i] = visited[i] = dp[i] = 0;
        }

        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            occ[v] = visited[v] = 1;
            mn = min(mn, v);
            mx = max(mx, v);
        }
        // dp[i] = minimum of the maximum value of the value i
        // note that this dp[i] is actually dp[i][x] where x is the minimum value of the multiset
        // but we can eliminate the second dimension by iterating x from mx to 1
        for (i = 0 ; i <= M; ++i) {
            dp[i] = i;
        }

        int maxr = mx, ans = mx - mn;
        // this i is actually the desired minimal value of the set
        for (i = mx; i >= 1; --i) {
            // using the property that only i | x, the dp value of x 
            // can be changed
            for (ll j = 1ll * i * i; j <= mx; j = j + i) {
                if (occ[j]) visited[dp[j]]--;
                dp[j] = min(dp[j], max(i, dp[j / i]));
                if (occ[j]) visited[dp[j]]++;
            }

            // if we find a way to eliminate maxr
            // we decrease the maximum right value
            while (!visited[maxr]) {
                maxr--;
            }

            if (i <= mn) {
                ans = min(ans, maxr - i);
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}