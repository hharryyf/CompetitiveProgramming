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
int bt[MAX_SIZE];
int a[MAX_SIZE][9];
bool cnt[259];
vector<int> mask[259];
pair<int, int> ansp;

bool check(int val, bool construct=false) {
    int i, j;
    memset(cnt, false, sizeof(cnt));

    for (i = 0 ; i < (1 << M); ++i) {
        mask[i].clear();
    }

    for (i = 1; i <= N; ++i) {
        int msk = 0;
        for (j = 0 ; j < M; ++j) {
            if (a[i][j] >= val) {
                msk |= (1 << j);
            }
        }

        cnt[msk] = true;
        debug("set mask %d to be true\n", msk);

        if (construct) {
            mask[msk].push_back(i);
        }
    }

    debug("check %d\n", val);
    for (i = 0; i < (1 << M); ++i) {
        if (cnt[i]) {
            debug("mask %d is fine\n", i);
            for (j = 0 ; j < (1 << M); ++j) {
                if (((j | i) == ((1 << M) - 1)) && cnt[j]) {
                    debug("mask %d is matching\n", j);
                    if (construct) {
                        ansp.first = mask[i].front();
                        ansp.second = mask[j].front();
                    }
                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);

    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j < M; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    int low = 0, high = 1000000000, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }

    debug("%d\n", ans);
    check(ans, true);
    printf("%d %d\n", ansp.first, ansp.second);
    return 0;
}