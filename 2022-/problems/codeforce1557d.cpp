#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 2097312
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

struct segt {
    pair<int, int> val, lz;
};

vector<pair<int, int>> g[MAX_SIZE >> 2];
vector<int> tmp, disc;

segt tree[MAX_SIZE];

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz.first != 0 || tree[index].lz.second != 0) {
        if (l != r) {
            tree[LEFT].val = max(tree[LEFT].val, tree[index].lz);
            tree[RIGHT].val = max(tree[RIGHT].val, tree[index].lz);
            tree[LEFT].lz = max(tree[LEFT].lz, tree[index].lz);
            tree[RIGHT].lz = max(tree[RIGHT].lz, tree[index].lz);
        }

        tree[index].lz = {0, 0};
    }
}

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.val = max(t1.val, t2.val);
    ret.lz = {0, 0};
    return ret;
}

void update(int start, int end, int l, int r, int index, int v, int pos) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].val = max(tree[index].val, make_pair(v, pos));
        tree[index].lz = make_pair(v, pos);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, v, pos);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v, pos);
    } else {
        update(start, end, l, MID, LEFT, v, pos);
        update(start, end, MID + 1, r, RIGHT, v, pos);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        return tree[index];
    }

    if (end <= MID) {
        return query(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return query(start, end, MID + 1, r, RIGHT);
    } 

    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int f[MAX_SIZE], dp[MAX_SIZE], visited[MAX_SIZE];

int main() {
    int i, N, M;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int v, l, r;
        scanf("%d%d%d", &v, &l, &r);
        g[v].emplace_back(l, r);
        tmp.push_back(l);
        tmp.push_back(r);
    }

    sort(tmp.begin(), tmp.end());
    
    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    int sz = disc.size();
    for (i = 1; i <= N; ++i) {
        for (auto &p : g[i]) {
            int id = lower_bound(disc.begin(), disc.end(), p.first) - disc.begin() + 1;
            p.first = id;
            id = lower_bound(disc.begin(), disc.end(), p.second) - disc.begin() + 1;
            p.second = id;
        }
    }

    for (i = 1; i <= N; ++i) {
        pair<int, int> v = {0, 0};
        for (auto p : g[i]) {
            auto r = query(p.first, p.second, 1, sz, 1).val;
            v = max(v, r);
        }

        f[i] = v.second;
        for (auto p : g[i]) {
            update(p.first, p.second, 1, sz, 1, v.first + 1, i);
        }

        dp[i] = v.first + 1;
        debug("dp[%d] = %d\n", i, dp[i]);       
    }

    printf("%d\n", N - tree[1].val.first);
    
    for (i = 1; i <= N; ++i) {
        if (dp[i] == tree[1].val.first) {
            while (i != 0) {
                visited[i] = 1;
                i = f[i];
            }
            break;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!visited[i]) {
            printf("%d ", i);
        }
    }

    printf("\n");
    return 0;
}