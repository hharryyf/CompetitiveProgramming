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

int a[MAX_SIZE];
int dp[MAX_SIZE];
int cnt[MAX_SIZE];
bool ok[MAX_SIZE][MAX_SIZE];

bool query(int l, int r) {
    if (r < l) return true;
    if ((r - l + 1) % 2 == 1) return false;
    return ok[l][r];
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            cnt[a[i]] = 0;
            dp[i] = 0;
        }

        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j){
                ok[i][j]  = false;      
            }
        }

        for (i = 1; i <= N; ++i) {
            int mx = 0;
            for (j = i; j <= N; ++j) {
                cnt[a[j]] = 0;
            }

            for (j = i; j <= N; ++j) {
                cnt[a[j]]++;
                mx = max(cnt[a[j]], mx);
                if ((j - i + 1) % 2 == 0 && mx <= (j - i + 1) / 2) {
                    ok[i][j] = true;
                }
            }
        }

        int ans = 0;
        for (i = 1; i <= N; ++i) {
            dp[i] = query(1, i - 1) ? 1 : -100000000;
            for (j = 1; j < i; ++j) {
                if (a[i] != a[j]) continue;
                if (query(j + 1, i - 1)) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            debug("dp[%d] = %d query = %d\n", i, dp[i], query(i + 1, N));
            if (query(i + 1, N)) {
                ans = max(ans, dp[i]);
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}