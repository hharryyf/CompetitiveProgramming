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

ll lcm(ll n,ll m){
    return n*m/gcd(n,m);
}

int ask(int x) {
    int s;
    cout << "? " << x << endl;
    cin >> s;
    return s; 
}

int main() {
    int N;
    cin >> N;
    int i, S = 0, low = 1, high = N * 2000 + 2000;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int h = ask(mid);
        if (h == 1) {
            S = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    int ans = 1e9;
    for (i = 1; i <= N; ++i) {
        int curr = ask(S / i);
        if (curr != 0) {
            ans = min(ans, curr * (S / i));
        }
    }

    cout << "! " << ans << endl;
    return 0;
}