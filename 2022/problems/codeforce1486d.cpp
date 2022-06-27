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

int N, K;
int a[MAX_SIZE], b[MAX_SIZE];
int pre[MAX_SIZE];

bool check(int val) {
    int i, mn = 0;
    for (i = 1; i <= N; ++i) {
        pre[i] = pre[i - 1];
        if (a[i] < val) {
            pre[i]--;
        } else {
            pre[i]++;
        }
    }

    for (i = K; i <= N; ++i) {
        mn = min(mn, pre[i - K]);
        if (pre[i] - mn > 0) return true;
    }

    return false;
}

int main() {
    int i;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    sort(b + 1, b + 1 + N);

    int low = 1, high = N, ans = b[1];
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(b[mid])) {
            ans = b[mid];
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}