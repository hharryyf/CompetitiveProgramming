#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
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

vector<int> g[MAX_SIZE];
int N;

int solve(int idx) {
    if (g[idx].empty()) return 0;
    int curr = g[idx].front(), cnt = 1;
    for (int i = 1; i < (int) g[idx].size(); ++i) {
        if (g[idx][i] % 2 != curr % 2) {
            cnt++;
            curr = g[idx][i];
        }
    }

    return cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        int i;
        for (i = 1; i <= N; ++i) {
            g[i].clear();
        }

        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            g[v].push_back(i);
        }

        for (i = 1; i <= N; ++i) {
            printf("%d ", solve(i));
        }
        printf("\n");
    }
    return 0;
}