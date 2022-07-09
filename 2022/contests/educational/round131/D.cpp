#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
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

vector<pair<int, int>> g[MAX_SIZE];
int pos[MAX_SIZE];
set<pair<int, int>> st;
int a[MAX_SIZE], N;
int l[MAX_SIZE], r[MAX_SIZE];

// smallest number such that idx / ans = val
int calcL(int idx, int val) {
    int low = 1, high = N, ret = 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if ((idx / mid) <= val) {
            ret = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}

// largest number such that idx / mid >= val
int calcR(int idx, int val) {
    int low = 1, high = N, ret = N;
    while (low <= high) {
        int mid = (low + high) / 2;
        if ((idx / mid) >= val) {
            ret = mid;
            low = mid + 1;
        } else { 
            high = mid - 1;
        }
    }

    return ret;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            g[i].clear();
        }

        st.clear();

        for (i = 1; i <= N; ++i) {
            l[i] = calcL(i, a[i]);
            r[i] = calcR(i, a[i]);
            g[l[i]].emplace_back(r[i], i);
        }

        for (i = 1; i <= N; ++i) {
            for (auto p : g[i]) {
                st.insert(p);
            }

            auto iter = st.begin();
            pos[iter->second] = i;
            st.erase(*iter);
        }

        for (i = 1; i <= N; ++i) {
            printf("%d ", pos[i]);
        }

        printf("\n");
    }
    return 0;
}