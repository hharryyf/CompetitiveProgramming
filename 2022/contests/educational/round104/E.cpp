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

int N[4], M[4];
int cost[4][MAX_SIZE];

vector<int> bad[4][150111];

int tree[MAX_SIZE];

int dp[MAX_SIZE];

const int inf = 700000000;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = dp[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return inf;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int i, j;
    for (i = 0 ; i < 4; ++i) scanf("%d", &N[i]);
    for (i = 0; i < 4; ++i) {
        for (j = 1; j <= N[i]; ++j) {
            scanf("%d", &cost[i][j]);
        }
    }

    for (i = 1 ; i <= 3; ++i) {
        scanf("%d", &M[i]);
        for (j = 1; j <= M[i]; ++j) {
            int x, y;
            scanf("%d%d", &x, &y);
            bad[i][y].push_back(x);
        }
    }

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 150111; ++j) {
            sort(bad[i][j].begin(), bad[i][j].end());
        }
    }

    for (i = 1; i <= N[0]; ++i) {
        dp[i] = cost[0][i];
    }

    build(1, N[0], 1);

    for (i = 1; i <= 3; ++i) {
        for (j = 1; j <= N[i]; ++j) {
            dp[j] = inf;
        }

        for (j = 1; j <= N[i]; ++j) {
            for (int k = 0 ; k < (int) bad[i][j].size() - 1; ++k) {
                int l = bad[i][j][k] + 1, r = bad[i][j][k+1] - 1;
                dp[j] = min(dp[j], query(l, r, 1, N[i-1], 1) + cost[i][j]);
            }

            if (bad[i][j].empty()) {
                dp[j] = min(dp[j], query(1, N[i-1], 1, N[i-1], 1) + cost[i][j]);
            } else {
                int l = bad[i][j].front(), r = bad[i][j].back();
                dp[j] = min(dp[j], query(1, l-1, 1, N[i-1], 1) + cost[i][j]);
                dp[j] = min(dp[j], query(r+1, N[i-1], 1, N[i-1], 1) + cost[i][j]);
            }
        }

        build(1, N[i], 1);
    }

    printf("%d\n", tree[1] < inf ? tree[1] : -1);
    return 0;
}