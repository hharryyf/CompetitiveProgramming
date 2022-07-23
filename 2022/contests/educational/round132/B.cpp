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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef long double ld;

const ll mod = 998244353;
const int infint = 1030000000;
const ll infll = 1e18 + 17;

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

ll ex_euclidian(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = ex_euclidian(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll extented_crt(vector<ll> m , vector<ll> r){
    int n = m.size();
    ll MM = m[0] , R = r[0] , x , y , d;
    for(int i = 1; i < n; ++i){
        d = ex_euclidian(MM , m[i] , x , y);
        if((r[i] - R) % d)return -1;
        x = (r[i] - R) / d * x % (m[i] / d);
        R += x * MM;
        MM = MM / d * m[i];
        R %= MM;
    }
    return R > 0 ? R : R + MM;
}

ll pre[MAX_SIZE], suf[MAX_SIZE];
ll a[MAX_SIZE];
int N, Q;

int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
    for (i = 2; i <= N; ++i) {
        pre[i] = pre[i-1];
        if (a[i] < a[i-1]) {
            pre[i] += a[i-1] - a[i];
        }
    }

    for (i = N - 1; i >= 1; --i) {
        suf[i] = suf[i+1];
        if (a[i] < a[i+1]) {
            suf[i] += a[i+1] - a[i];
        }
    }

    while (Q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (r > l) {
            printf("%lld\n", pre[r] - pre[l]);
        } else {
            printf("%lld\n", -suf[l] + suf[r]);
        }
    }
    return 0;
}