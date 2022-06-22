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

const int inf = 1e9 + 7;
int N, M;
int a[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];
vector<int> pos1, pos2;

int main() {
    int i, j;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        for (j = 1; j < MAX_SIZE; ++j) {
            dp[i][j] = inf;
        }
    }

    dp[0][0] = 0;
    pos1.push_back(0);
    pos2.push_back(0);
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        if (a[i] == 0) {
            pos1.push_back(i);
        } else {
            pos2.push_back(i);
        }
    }

    N = (int) pos1.size();
    M = (int) pos2.size();
    N--;
    M--;
    if (M == 0) {
        printf("0\n");
        return 0;
    }
    int ans = inf;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            dp[i][j] = min(dp[i-1][j-1] + abs(pos1[i] - pos2[j]), dp[i-1][j]);
            if (j == M) {
                ans = min(ans, dp[i][j]);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}