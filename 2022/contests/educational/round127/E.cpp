#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
#define MAX_SIZE 262192
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

int N;
ll dp[MAX_SIZE];
char s[MAX_SIZE];

string solve(int idx) {
    if (idx >= (1 << N)) return "";
    string ret;
    ret += s[idx];
    dp[idx] = 1;
    auto L = solve(idx * 2);
    auto R = solve(idx * 2 + 1);
    if (L != "" && R != "") {
        if (L == R) {
            dp[idx] = mul(dp[idx * 2], dp[idx * 2 + 1]);
            ret.append(L);
            ret.append(R);
        } else if (L < R) {
            dp[idx] = mul(mul(dp[idx * 2], dp[idx * 2 + 1]), 2);
            ret.append(L);
            ret.append(R);
        } else {
            dp[idx] = mul(mul(dp[idx * 2], dp[idx * 2 + 1]), 2);
            ret.append(R);
            ret.append(L);
        }
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    scanf("%s", s + 1);
    solve(1);
    printf("%lld\n", dp[1]);
    return 0;
}