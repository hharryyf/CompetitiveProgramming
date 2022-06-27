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

int N, M;
char s[MAX_SIZE], t[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];

int main() {
    int i, j, ans = 0;
    scanf("%d%d", &N, &M);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (s[i] == t[j]) {
                dp[i][j] = max(max(dp[i-1][j-1] + 2, max(dp[i-1][j], dp[i][j-1]) - 1), dp[i][j]);
            } else {
                dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i][j-1]) - 1);
            }

            ans = max(ans, dp[i][j]);
        }
    }

    printf("%d\n", ans);
    return 0;
}