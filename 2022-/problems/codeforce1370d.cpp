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

int N, K;
int a[MAX_SIZE];

bool check(int mid) {
    int i;
    vector<int> good;
    for (i = 1; i <= N; ++i) {
        if (a[i] <= mid) good.push_back(i);
    }

    // check if the good positions can be odd
    int pre = -1, cnt = 0, target = (K + 1) / 2;
    for (auto pos : good) {
        if (pos - pre >= 2) {
            pre = pos;
            cnt++;
        }
    }

    if (cnt > target) return true;

    if (cnt == target && K % 2 == 1) return true;

    if (cnt == target && pre != N) return true;
    // check if the good positions can be even
    pre = 0, cnt = 0, target = K / 2;

    for (auto pos : good) {
        if (pos - pre >= 2) {
            pre = pos;
            cnt++;
        }
    }

    if (cnt > target) return true;

    if (cnt == target && K % 2 == 0) return true;

    if (cnt == target && pre != N) return true;

    return false;
}

int main() {
    int i;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);

    int ans = 1000000000, low = 1, high = 1000000000;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}