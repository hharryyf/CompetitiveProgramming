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
 
ll fac[MAX_SIZE], ifac[MAX_SIZE];
 
void init_1() {
    int i;
    fac[0] = ifac[0] = 1;
    for (i = 1 ; i < MAX_SIZE; ++i) {
        fac[i] = mul(fac[i-1], i);
        ifac[i] = mul(ifac[i-1], qpow(i, mod - 2));
    }
}
 
ll C(int n, int k) {
    if (n < k || k < 0) return 0;
    return mul(fac[n], mul(ifac[n-k], ifac[k]));
}

/*
    Each number can be interpreted as i + k_i and k_i != 0
    The best arrangement is definitely half the number takes + k_i and the other half takes - k_i
    If the total elements is odd, we can half two possible ways one is n/2 takes + k_i, n - n / 2 take -k_i
    Or n/2 + 1 takes +k_i while n/2 takes -k_i
*/

void solve(int N, int l, int r) {
    ll ans = mul(min(1 - l, r - N), C(N, N / 2));
    if (N % 2 == 1) {
        ans = add(ans, mul(min(1 - l, r - N), C(N, N / 2 + 1)));
    }

    int k = min(1 - l, r - N) + 1;
    while (true) {
        int L = max(1, l + k);
        int R = min(N, r - k);
        if (R + 1 < L) break;
        // this is when there's one side has restriction
        ans = add(ans, C(R + 1 - L, N / 2 - (L - 1)));
        if (N % 2 == 1) {
            ans = add(ans, C(R + 1 - L, N / 2 - (L - 1) + 1));
        }

        k++;
    }

    printf("%lld\n", ans);
}

int main() {
    init_1();
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n, l, r;
        scanf("%d%d%d", &n, &l, &r);
        solve(n, l, r);
    }
    return 0;
}