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

int N, M;

// mask --> (price, id)
vector<pair<int, int>> price[(1 << 9) + 2];
// how many friends with this bitmask
int cntbt[(1 << 9) + 2];

// mask[i][0] --> minimum price for this maximum count
// mask[i][1] --> index of the first pizza
// mask[i][2] --> index of the second pizza
array<int, 3> mask[(1 << 9) + 2];

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        int f, bt = 0;
        scanf("%d", &f);
        for (j = 1; j <= f; ++j) {
            int v;
            scanf("%d", &v);
            v--;
            bt |= (1 << v);
        }

        cntbt[bt]++;
    }

    for (i = 1; i <= M; ++i) {
        int p, f, bt = 0;
        scanf("%d%d", &p, &f);
        for (j = 1; j <= f; ++j) {
            int v;
            scanf("%d", &v);
            v--;
            bt |= (1 << v);
        }

        price[bt].emplace_back(p, i);
    }

    for (i = 0 ; i < (1 << 9); ++i) {
        sort(price[i].begin(), price[i].end());
    }
    
    for (i = 0 ; i < (1 << 9); ++i) {
        mask[i][0] = 2e9 + 4;
    }

    for (i = 0 ; i < (1 << 9); ++i) {
        for (j = i ; j < (1 << 9); ++j) {
            if (i == j && (int) price[i].size() >= 2) {
                if (mask[i][0] >= price[i][0].first + price[i][1].first) {
                    mask[i][0] = price[i][0].first + price[i][1].first;
                    mask[i][1] = price[i][0].second;
                    mask[i][2] = price[i][1].second;
                }
            } else if (i != j && !price[i].empty() && !price[j].empty()) {
                if (mask[i | j][0] >= price[i].front().first + price[j].front().first) {
                    mask[i | j][0] = price[i].front().first + price[j].front().first;
                    mask[i | j][1] = price[i].front().second;
                    mask[i | j][2] = price[j].front().second;
                }
            }
        }
    }

    vector<array<int, 3>> res;

    for (i = 0 ; i < (1 << 9); ++i) {
        if (!mask[i][1]) continue;
        int curr = 0;
        for (j = 0 ; j <= i; ++j) {
            if ((i & j) == j) {
                curr += cntbt[j];
            }
        }

        res.push_back({-curr, mask[i][0], i});
    }

    sort(res.begin(), res.end());
    assert(!res.empty());

    printf("%d %d\n", mask[res[0][2]][1], mask[res[0][2]][2]);
    return 0;
}