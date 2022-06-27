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

vector<pair<int, int>> pt;
vector<int> Y;

int main() {
    for (int i = 0; i < 3; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        pt.emplace_back(x, y);
        Y.push_back(y);
    }

    sort(Y.begin(), Y.end());
    sort(pt.begin(), pt.end());

    vector<array<int, 4>> ans;
    ans.push_back({pt[0].first, Y[1], pt[2].first, Y[1]});
    for (auto s : pt) {
        if (s.second != Y[1]) {
            ans.push_back({s.first, s.second, s.first, Y[1]});
        }
    }

    printf("%d\n", (int) ans.size());
    for (auto v : ans) {
        printf("%d %d %d %d\n", v[0], v[1], v[2], v[3]);
    }
    return 0;
}