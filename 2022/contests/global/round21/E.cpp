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
    if (n < k) return 0;
    return mul(fac[n], mul(ifac[n-k], ifac[k]));
}
 
int N, a[MAX_SIZE];

/*
    Contribution to white point (x, y) is C(x + y, x)
    Contribution to the ith row is sum(C(x + y,x), y = 0..a[x]-1) = C(x+a[x], (x+1))
*/

int main() {
    int i;
    init_1();
    scanf("%d", &N);
    for (i = 0 ; i <= N; ++i) scanf("%d", &a[i]);
    ll ans = 0;
    for (i = 0 ; i <= N; ++i) {
        ans = add(ans, C(i + a[i], i + 1));
    }

    printf("%lld\n", ans);
    return 0;
}