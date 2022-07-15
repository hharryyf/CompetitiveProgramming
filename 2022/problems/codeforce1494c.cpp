#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 201011
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

int solve(vector<int> &box, vector<int> &special) {
    if (box.empty() || special.empty()) return 0;
    if (box.front() > special.back()) return 0;
    int idx = lower_bound(special.begin(), special.end(), box.front()) - special.begin();
    int ssz = special.size();
    int bsz = box.size();
    int i, j, ret = 0;
    vector<int> cnt(bsz);
    for (i = 0; i < bsz; ++i) {
        if (binary_search(special.begin(), special.end(), box[i])) cnt[i] = 1;
    }

    for (i = 1; i < bsz; ++i) {
        cnt[i] += cnt[i-1];
    }

    for (i = idx, j = 0; i < ssz; ++i) {
        while (j < bsz - 1 && special[i] + j >= box[j + 1]) {
            ++j;
        }

        debug("move to special position %d, j = %d\n", special[i], j);
        // [0, j] are all the boxes located consecutively
        // [j + 1, bsz - 1] are all the boxes located seperately
        int ed = upper_bound(special.begin(), special.end(), special[i] + j) - special.begin();
        int curr = ed - i;
        debug("curr = %d\n", ed - i);
        if (j + 1 <= bsz - 1) {
            curr = curr + cnt[bsz - 1] - cnt[j];
        }
        debug("original + curr = %d\n", curr);
        ret = max(ret, curr);
    }

    return ret;
}

int a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, M, i;
        scanf("%d%d",&N, &M);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        for (i = 1; i <= M; ++i) {
            scanf("%d", &b[i]);
        }

        vector<int> box, special;
        for (i = 1; i <= N; ++i) {
            if (a[i] > 0) box.push_back(a[i]);
        }

        for (i = 1; i <= M; ++i) {
            if (b[i] > 0) special.push_back(b[i]);
        }

        int ans = solve(box, special);   
        box.clear();
        special.clear();
        for (i = 1; i <= N; ++i) {
            if (a[i] < 0) {
                box.push_back(-a[i]);
            }
        }

        for (i = 1; i <= M; ++i) {
            if (b[i] < 0) {
                special.push_back(-b[i]);
            }
        }

        reverse(box.begin(), box.end());
        reverse(special.begin(), special.end());
        ans = ans + solve(box, special);

        printf("%d\n", ans);
        
    }
    return 0;
}