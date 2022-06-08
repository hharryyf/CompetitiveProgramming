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
    int ldec, rdec, lval, rval, len;
    ll ans; 
};


segt tree[MAX_SIZE];

void print(segt t) {
    debug("ldec=%d, rdec=%d, lval=%d, rval=%d, len=%d, ans=%lld\n", t.ldec, t.rdec, t.lval, t.rval, t.len, t.ans);
}

segt pullup(segt t1, segt t2) {
    segt ret;
    debug("merge---\n");
    //print(t1);
    //print(t2);
    debug("get---\n");
    ret.lval = t1.lval;
    ret.rval = t2.rval;
    ret.len = t1.len + t2.len;
    ret.ldec = t1.ldec + ((t1.ldec == t1.len && t1.rval <= t2.lval) ? t2.ldec : 0);
    ret.rdec = t2.rdec + ((t2.rdec == t2.len && t1.rval <= t2.lval) ? t1.rdec : 0);
    ret.ans = t1.ans + t2.ans;
    if (t1.rval <= t2.lval) {
        ret.ans += 1ll * t1.rdec * t2.ldec;
    }
    //print(ret);
    return ret;
}

void update(int pt, int l, int r, int index, int v) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index].lval = tree[index].rval = v;
        tree[index].len = 1;
        tree[index].ans = 0;
        tree[index].ldec = tree[index].rdec = 1;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, v);
    } else {
        update(pt, MID + 1, r, RIGHT, v);
    }
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int a[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].len = 1;
        tree[index].ans = 0;
        tree[index].ldec = tree[index].rdec = 1;
        tree[index].lval = tree[index].rval = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int N, Q, i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }
    build(1, N, 1);
    while (Q-- > 0) {
        int tp, l, r;
        scanf("%d%d%d", &tp, &l, &r);
        if (tp == 1) {
            update(l, 1, N, 1, r);
        } else {
            printf("%lld\n", query(l, r, 1, N, 1).ans + r - l + 1);
        }
    }
    return 0;
}