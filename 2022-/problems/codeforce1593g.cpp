#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1000011
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


int cnt[MAX_SIZE][2];
char s[MAX_SIZE];
int N;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s + 1);
        N = strlen(s + 1);
        for (int i = 1; i <= N; ++i) {
            cnt[i][0] = cnt[i-1][0] + (i % 2 == 0 && (s[i] == '[' || s[i] == ']'));
            cnt[i][1] = cnt[i-1][1] + (i % 2 == 1 && (s[i] == '[' || s[i] == ']'));
        }

        int Q;
        scanf("%d", &Q);
        while (Q-- > 0) {
            int l, r;
            scanf("%d%d", &l, &r);
            int odd = cnt[r][1] - cnt[l-1][1], even = cnt[r][0] - cnt[l-1][0];
            printf("%d\n", max(odd, even) - min(odd, even));
        }
    }
    return 0;
}