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

int a[MAX_SIZE], b[MAX_SIZE];
bool hasval[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, N, S;
        scanf("%d%d", &N, &S);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            hasval[i] = false;
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &b[i]);
            if (b[i] != -1) hasval[b[i]] = true;
        }
        
        vector<int> vc;
        bool ok = true;
        for (i = 1; i <= N; ++i) {
            if (b[i] != -1 && a[i] - S > b[i]) {
                ok = false;
                break;
            }
        }

        for (i = 1; i <= N; ++i) {
            if (!hasval[i]) {
                vc.push_back(i);
            }
        }

        if (!ok) {
            printf("0\n");
            continue;
        }

        vector<int> cnt;

        for (i = 1; i <= N; ++i) {
            if (b[i] == -1) {
                int idx = lower_bound(vc.begin(), vc.end(), a[i] - S) - vc.begin();        
                cnt.push_back((int) vc.size() - idx);
            }
        }

        sort(cnt.begin(), cnt.end());

        ll ans = 1;
        int dt = 0;
        for (auto c : cnt) {
            ans = mul(ans, (c - dt));
            dt++;
        }

        printf("%lld\n", ans);
    }
    return 0;
}