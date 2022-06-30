#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

char s[2][MAX_SIZE];

int main() {
    int T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        scanf("%s", s[0] + 1);
        scanf("%s", s[1] + 1);
        int i, ans = 0;
        bool meet11 = false, meet00 = false;
        for (i = 1; i <= N; ++i) {
            if (s[0][i] != s[1][i]) {
                meet11 = meet00 = false;
                ans += 2;
            } else if (s[0][i] == '0') {
                ans++;
                if (meet11) {
                    ans++;
                    meet00 = false;
                    meet11 = false;
                } else {
                    meet00 = true;
                }
            } else {
                if (meet00) {
                    ans++;
                    meet00 = false;
                    meet11 = false;
                } else {
                    meet11 = true;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}