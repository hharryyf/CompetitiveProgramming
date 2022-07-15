#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
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
typedef long double ld;

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

ll a[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int cntpos = 0, cntneg = 0;
        int N;
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%lld", &a[i]);
            if (a[i] < 0) cntneg++;
            if (a[i] > 0) cntpos++;
        }

        if (cntneg >= 3 || cntpos >= 3) {
            printf("NO\n");
            continue;
        }

        vector<ll> b;
        int c0 = 0;
        for (int i = 1; i <= N; ++i) {
            if (a[i] != 0) {
                b.push_back(a[i]);
            } else {
                if (c0 <= 3) {
                    b.push_back(0);
                    c0++;
                }
            }
        }

        int i, j, k, l, sz = b.size();
        bool ok = true;
        for (i = 0 ; i < sz; ++i) {
            for (j = i + 1; j < sz; ++j) {
                for (k = j + 1; k < sz; ++k) {
                    bool f = false;
                    for (int l = 0 ; l < sz; ++l) {
                        if (b[l] == b[i] + b[j] + b[k]) {
                            f = true;
                        }
                    }

                    if (!f) ok = false;
                }
            }
        }

        printf("%s\n", ok ? "YES" : "NO");
    }
    return 0;
}