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

int pre[201][200011];
vector<int> g[201];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j;
        scanf("%d", &N);
        for (i = 0; i <= 200; ++i) g[i].clear();
        for (i = 0; i <= 200; ++i) {
            for (j = 1; j <= N; ++j) {
                pre[i][j] = 0;
            }
        }

        int ans = 0;
        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            g[v].push_back(i);
            pre[v][i] = 1;
            for (j = 1; j <= 200; ++j) {
                pre[j][i] += pre[j][i-1];
                ans = max(ans, pre[j][i]);
            }
        }

        
        for (i = 1; i <= 200; ++i) {
            if (g[i].empty()) continue;
            int l = 0, r = (int) g[i].size() - 1, x = 1;
            while (l < r) {
                int Lpos = g[i][l] + 1, Rpos = g[i][r] - 1;
                for (j = 1; j <= 200; ++j) {
                    ans = max(ans, 2 * x + pre[j][Rpos] - pre[j][Lpos - 1]);
                }
                l++;
                r--;
                x++;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}