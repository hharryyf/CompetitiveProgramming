#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 200011
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

int dp[MAX_SIZE][2];
char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s + 1);
        int i, N = strlen(s + 1);
        for (i = 1; i <= N; ++i) {
            dp[i][0] = dp[i][1] = 0;
        }

        ll ans = 0;
        for (i = 1; i <= N; ++i) {
            if (s[i] == '1') {
                dp[i][1] = dp[i-1][0] + 1;
            } else if (s[i] == '0') {
                dp[i][0] = dp[i-1][1] + 1;
            } else {
                dp[i][1] = dp[i-1][0] + 1;
                dp[i][0] = dp[i-1][1] + 1;
            }

            ans = ans + max(dp[i][0], dp[i][1]);
        }

        printf("%lld\n", ans);
    }
    return 0;
}