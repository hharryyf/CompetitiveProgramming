#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 524312
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

int a[52][52];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, M, i, j;
        scanf("%d%d", &N, &M);
        for (i = 0 ; i < N - 1; i = i + 2) {
            for (j = 0 ; j < M - 1; j = j + 2) {
                if (i == 0 && j == 0) {
                    a[i][j] = 1;
                    a[i][j+1] = 0;
                    a[i+1][j] = 0;
                    a[i+1][j+1] = 1; 
                } else {
                    if (j == 0) {
                        if (a[i-2][j] == 1) {
                            a[i][j] = 0;
                            a[i][j+1] = 1;
                            a[i+1][j] = 1;
                            a[i+1][j+1] = 0;
                        } else {
                            a[i][j] = 1;
                            a[i][j+1] = 0;
                            a[i+1][j] = 0;
                            a[i+1][j+1] = 1;
                        }
                    } else {
                        if (a[i][j-2] == 1) {
                            a[i][j] = 0;
                            a[i][j+1] = 1;
                            a[i+1][j] = 1;
                            a[i+1][j+1] = 0;
                        } else {
                            a[i][j] = 1;
                            a[i][j+1] = 0;
                            a[i+1][j] = 0;
                            a[i+1][j+1] = 1;
                        }
                    }
                }
            }
        }

        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < M; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}