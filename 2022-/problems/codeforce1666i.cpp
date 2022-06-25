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


int scan(int x, int y) {
    cout << "SCAN " << x << " " << y << endl;
    cin >> x;
    return x;
}

int dig(int x, int y) {
    cout << "DIG " << x << " " << y << endl;
    cin >> x;
    return x;
}

void solve(int N) {
    int r1 = scan(1, 1), r2 = scan(N, 1);
    int c1 = r1 + 4, c2 = r2 + 2 - 2 * N;
    int x12 = (c1 - c2) / 2;
    int y12 = (c1 + c2) / 2;
    int r3 = scan(x12 / 2, 1), r4 = scan(1, y12 / 2);
    int y21 = r4 + 2 - (c1 - c2) / 2;
    int x21 = r3 + 2 - (c1 + c2) / 2;
    int x2 = (x21 + x12) / 2, x1 = x12 - x2;
    int y2 = (y21 + y12) / 2, y1 = y12 - y2;
    if (dig(x1, y1)) {
        dig(x2, y2);
    } else {
        dig(x1, y2);
        dig(x2, y1);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int M, N;
        scanf("%d%d", &M, &N);
        solve(M);
    }
    return 0;
}