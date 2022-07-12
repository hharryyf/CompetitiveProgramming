#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200011
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

ll a[MAX_SIZE];

int main() {
    int N;
    ll X;
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        cin >> N >> X;
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
        }

        ll mn = a[1], mx = a[1];
        ll curr = 0;
        for (i = 1; i < N; ++i) {
            curr = curr + llabs(a[i] - a[i+1]);
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }

        mn = min(mn, a[N]);
        mx = max(mn, a[N]);

        ll ans = 1e18;
        if (mn > 1 && mx >= X) {
            for (i = 1; i < N; ++i) {
                ans = min(ans, curr + llabs(a[i] - 1) + llabs(a[i + 1] - 1) - llabs(a[i+1] - a[i]));
            }

            ans = min(ans, curr + llabs(a[1] - 1));
            ans = min(ans, curr + llabs(a[N] - 1));
        } else if (mn == 1 && mx < X) {
            for (i = 1; i < N; ++i) {
                ans = min(ans, curr + llabs(a[i] - X) + llabs(a[i + 1] - X) - llabs(a[i+1] - a[i]));
            }

            ans = min(ans, curr + llabs(a[1] - X));
            ans = min(ans, curr + llabs(a[N] - X));
        } else if (mn > 1 && mx < X) {
            ans = min(ans, curr + llabs(X - 1) + llabs(a[1] - X));
            debug("ans = %lld\n", ans);
            ans = min(ans, curr + llabs(X - 1) + llabs(a[1] - 1));
            debug("ans = %lld\n", ans);
            ans = min(ans, curr + llabs(X - 1) + llabs(a[N] - X));
            debug("ans = %lld\n", ans);
            ans = min(ans, curr + llabs(X - 1) + llabs(a[N] - 1));
            debug("ans = %lld\n", ans);
            for (i = 1; i < N; ++i) {
                ans = min(ans, curr - llabs(a[i+1] - a[i]) + llabs(X - a[i]) + X - 1 + llabs(a[i+1] - 1));
                debug("ans = %lld\n", ans);
                ans = min(ans, curr - llabs(a[i+1] - a[i]) + llabs(a[i] - 1) + X - 1 + llabs(a[i+1] - X));
                debug("ans = %lld\n", ans);
            }

            multiset<ll> val;
            val.insert(llabs(a[1] - 1));
            val.insert(llabs(a[N] - 1));
            for (i = 1; i < N; ++i) {
                val.insert(llabs(a[i] - 1) + llabs(a[i+1] - 1) - llabs(a[i] - a[i+1]));
            }

            for (i = 1; i < N; ++i) {
                ll c = llabs(a[i] - 1) + llabs(a[i+1] - 1) - llabs(a[i] - a[i+1]);
                val.erase(val.find(c));
                ll dc = llabs(a[i] - X) + llabs(a[i+1] - X) - llabs(a[i] - a[i+1]);
                ll dc2 = *val.begin();
                ans = min(ans, curr + dc + dc2);
                debug("tans = %lld\n", curr + dc + dc2);
                val.insert(c);
            }

            val.erase(val.find(llabs(a[1] - 1)));
            ans = min(ans, curr + *val.begin() + llabs(a[1] - X));
            val.insert(llabs(a[1] - 1));
            val.erase(val.find(llabs(a[N] - 1)));
            debug("ans = %lld\n", ans);
            ans = min(ans, curr + *val.begin() + llabs(a[N] - X));
            debug("ans = %lld\n", ans);
            debug("curr = %lld\n", curr);
        } else {
            ans = curr;
        }

        printf("%lld\n", ans);
    }
    return 0;
}