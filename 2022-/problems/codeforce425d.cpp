#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

vector<int> g[MAX_SIZE];
const int maxx = 100000;
const int block_size = 320;
bool isheavy[MAX_SIZE];
vector<int> heavy;

bool ok(int x, int y) {
    if (x < 0 || x > maxx) return false;
    return binary_search(g[x].begin(), g[x].end(), y);
} 

int main() {
    int N, i, j, k;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
    }

    for (i = 0 ; i <= maxx; ++i) {
        sort(g[i].begin(), g[i].end());
        if ((int) g[i].size() > block_size) {
            heavy.push_back(i);
            isheavy[i] = true;
        }
    }

    ll ans = 0;

    // squares formed by left side heavy - right side heavy
    for (i = 0 ; i < (int) heavy.size(); ++i) {
        for (j = i + 1; j < (int) heavy.size(); ++j) {
            int d = heavy[j] - heavy[i];
            for (auto y : g[heavy[i]]) {
                // (i, y), (i + d, y) (i, y + d) (i + d, y + d)
                if (ok(heavy[i] + d, y) && ok(heavy[i], y + d) && ok(heavy[i] + d, y + d)) {
                    ans++;
                }
            }
        }
    }

    // squares formed by left side light - right side light
    // squares formed by left side light - right side heavy
    // squares formed by left side heavy - right side light
    for (i = 0 ; i <= maxx; ++i) {
        if (!isheavy[i]) {
            for (j = 0 ; j < (int) g[i].size(); ++j) {
                for (k = j + 1; k < (int) g[i].size(); ++k) {
                    int y1 = g[i][j], y2 = g[i][k];
                    int d = y2 - y1;
                    if (i + d <= maxx) {
                        if (ok(i + d, y1) && ok(i + d, y2)) ans++;
                    }

                    if (i - d >= 0 && isheavy[i - d]) {
                        if (ok(i - d, y1) && ok(i - d, y2)) ans++;
                    }
                }
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}