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

const int inf = 1e9 + 7;

struct segt {
    // whether the value is 0 or 1
    int val;
    // lazy tag for val
    int lz;
    // the minimum right endpoint for each l such that [l, r] = 1 exists
    int rmin;
};

segt tree[MAX_SIZE];


void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != inf) {
        if (l != r) {
            tree[LEFT].val = min(tree[LEFT].val, tree[index].lz);
            tree[RIGHT].val = min(tree[RIGHT].val, tree[index].lz);
            tree[LEFT].lz = min(tree[LEFT].lz, tree[index].lz);
            tree[RIGHT].lz = min(tree[RIGHT].lz, tree[index].lz);
        }

        tree[index].lz = inf;
    }
}

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.lz = inf;
    ret.rmin = min(t1.rmin, t2.rmin);;
    ret.val = max(t1.val, t2.val);
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].val = 1;
        tree[index].lz = inf;
        tree[index].rmin = inf;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}


void update(int start, int end, int l, int r, int index, int v=-1) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        if (v != -1) {
            tree[index].rmin = min(tree[index].rmin, v);
        } else {
            tree[index].val = tree[index].lz = 0;
        }
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, v);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v);
    } else {
        update(start, end, l, MID, LEFT, v);
        update(start, end, MID + 1, r, RIGHT, v);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

// query the rightmost 1 in a range [start, end]
int queryR(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -inf;
    pushdown(l, r, index);
    if (tree[index].val <= 0) return -inf;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[RIGHT].val > 0) return queryR(start, end, MID + 1, r, RIGHT);
        return queryR(start, end, l, MID, LEFT);
    }

    if (end <= MID) {
        return queryR(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return queryR(start, end, MID + 1, r, RIGHT);
    } 

    return max(queryR(start, end, l, MID, LEFT), queryR(start, end, MID + 1, r, RIGHT));
}

// query the leftmost 1 in the range [start, end]
int queryL(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return inf;
    pushdown(l, r, index);
    if (tree[index].val <= 0) return inf;
    if (l == r) return l;
    if (start <= l && r <= end) {
        if (tree[LEFT].val > 0) return queryL(start, end, l, MID, LEFT);
        return queryL(start, end, MID + 1, r, RIGHT);
    }

    if (end <= MID) {
        return queryL(start, end, l, MID, LEFT);
    } else if (start >= MID + 1) {
        return queryL(start, end, MID + 1, r, RIGHT);
    } 

    return min(queryL(start, end, l, MID, LEFT), queryL(start, end, MID + 1, r, RIGHT));
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

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    build(0, N + 1, 1);
    while (Q-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 0) {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            if (x == 0) {
                update(l, r, 0, N + 1, 1, -1);
                debug("set [%d,%d] to 0\n", l, r);
            } else {
                update(l, l, 0, N + 1, 1, r);
            }
        } else {
            int pos;
            scanf("%d", &pos);
            if (query(pos, pos, 0, N + 1, 1).val == 0) {
                printf("NO\n");
            } else {
                debug("position = %d\n", pos);
                int L = queryR(0, pos - 1, 0, N + 1, 1) + 1, R = queryL(pos + 1, N + 1, 0, N + 1, 1) - 1;
                debug("left 0= %d, right 0=%d\n", L, R);
                int nxt = query(L, pos, 0, N + 1, 1).rmin;
                debug("minimum rightend %d\n", nxt);
                if (nxt <= R) {
                    printf("YES\n");
                } else {
                    printf("N/A\n");
                }
            }
        }
    }
    return 0;
}