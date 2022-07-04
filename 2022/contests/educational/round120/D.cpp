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

const int mod = 998244353;

inline int add(int x,int y){
    return ((x + y) % mod + mod) % mod;
}

inline int mul(int x,int y){
    return 1ll * x * y % mod;
}

inline int qpow(int x,int n){
    int ret= 1;
    while(n > 0){
        if(n & 1) ret = mul(ret, x);
        x = mul(x, x);
        n >>= 1;
    }

    return ret;
}

int gcd(int n,int m){
    return n==0?m:gcd(m%n,n);
}

int N, K;
int C[MAX_SIZE][MAX_SIZE];
int cnt[MAX_SIZE];
char s[MAX_SIZE];

int main() {
    int i, j;
    C[0][0] = 1;
    for (i = 1 ; i < MAX_SIZE; ++i) {
        for (j = 0; j < MAX_SIZE; ++j) {
            C[i][j] = add(C[i-1][j], j > 0 ? C[i-1][j-1] : 0);
        }
    }

    scanf("%d%d", &N, &K);
    scanf("%s", s + 1);
    for (i = 1; i <= N; ++i) {
        cnt[i] = cnt[i-1] + (s[i] == '1');
    }

    int ans = 1;

    if (cnt[N] >= K) {
        for (i = 1; i <= N; ++i) {
            for (j = i + 1; j <= N; ++j) {
                if (cnt[j] - cnt[i-1] > K) break;
                int c1 = cnt[j] - cnt[i-1], c0 = j - i + 1 - c1;
                if (s[i] == '0') {
                    c1--;
                } else {
                    c0--;
                }
                if (s[j] == '0') {
                    c1--;
                } else {
                    c0--;
                }

                if (c0 < 0 || c1 < 0) continue;
                ans = add(ans, C[c0 + c1][c0]);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}