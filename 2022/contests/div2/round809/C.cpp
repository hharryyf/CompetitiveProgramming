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

ll odd[MAX_SIZE], even[MAX_SIZE], h[MAX_SIZE];
ll a[MAX_SIZE];
int N;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        for (i = 1; i <= N + 7; ++i) {
            a[i] = 0;
            odd[i] = even[i] = 0;
        }

        for (i = 1; i <= N; ++i) {
            scanf("%lld", &h[i]);
        }

        for (i = 2; i <= N - 1; ++i) {
            ll target = max(h[i-1], h[i+1]) + 1;
            if (h[i] < target) {
                a[i] = target - h[i];
            }
        }

        for (i = 2; i <= N + 7; ++i) {
            if (i % 2 == 0) {
                even[i] = even[i-1] + a[i];
                odd[i] = odd[i-1];
            } else {
                even[i] = even[i-1];
                odd[i] = odd[i-1] + a[i];
            }
        }

        if (N % 2 == 1) {
            printf("%lld\n", even[N + 7]);
        } else {
            ll ans = odd[N + 7];
            for (i = 2; i <= N - 2; i = i + 2) {
                ans = min(ans, even[i] + odd[N + 7] - odd[i + 2]);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}