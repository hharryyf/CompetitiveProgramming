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

int N;
ll K;
int a[MAX_SIZE];

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        ll sm = 0;
        scanf("%d%lld", &N, &K);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            sm += a[i];
        }

        sort(a + 1, a + 1 + N);

        ll ans = max(0ll, sm - K);
        if (ans == 0) {
            printf("0\n");
            continue;
        }

        int cnt = 0;
        ll df = 0;
        for (i = N; i >= 2; --i) {
            cnt++;
            df += a[i] - a[1];
            if (sm - K - df <= 0) ans = min(ans, 1ll * cnt);
            // total operation = cnt + p
            // where df + p * (cnt + 1) >= sm - K
            else {
                ans = min(ans, max(0ll, (sm - K - df) / (cnt + 1) + ((sm - K - df) % (cnt + 1) != 0) + cnt));
            }
        }

        printf("%lld\n", ans);
    }
    
    return 0;
}