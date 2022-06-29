#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 511
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
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

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N;
        scanf("%d", &N);
        vector<int> odd, even, a;
        for (int i = 0 ; i < N; ++i) {
            int v;
            scanf("%d", &v);
            if (v % 2 == 1) {
                odd.push_back(v);
            } else {
                even.push_back(v);
            }
        }

        for (auto v : even) {
            a.push_back(v);
        }

        for (auto v : odd) {
            a.push_back(v);
        }

        int ans = 0;
        for (int i = 0 ; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (gcd(a[i], a[j] * 2) > 1) {
                    ans++;
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}