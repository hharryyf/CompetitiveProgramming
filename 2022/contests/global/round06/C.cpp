#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 111
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

int main() {
    int N, M, i, j;
    scanf("%d%d", &N, &M);
    if (N == 1 && M == 1) {
        printf("0\n");
    } else {
        if (N == 1) {
            for (i = 1; i <= M; ++i) {
                printf("%d ", i + 1);
            }
            printf("\n");
        } else if (M == 1) {
            for (i = 1; i <= N; ++i) {
                printf("%d\n", i + 1);
            }
        } else {
            for (i = 1; i <= N; ++i) {
                for (j = 1; j <= M; ++j) {
                    printf("%d ", i * (j + N));
                }
                printf("\n");
            }
        }
    }
    return 0;
}