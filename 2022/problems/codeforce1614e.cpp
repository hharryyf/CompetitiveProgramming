#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 45000011
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
const int infint = 1030000000;
const ll infll = 1e18 + 17;

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

ll ex_euclidian(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = ex_euclidian(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll extented_crt(vector<ll> m , vector<ll> r){
    int n = m.size();
    ll MM = m[0] , R = r[0] , x , y , d;
    for(int i = 1; i < n; ++i){
        d = ex_euclidian(MM , m[i] , x , y);
        if((r[i] - R) % d)return -1;
        x = (r[i] - R) / d * x % (m[i] / d);
        R += x * MM;
        MM = MM / d * m[i];
        R %= MM;
    }
    return R > 0 ? R : R + MM;
}

struct node {
    int mn, mx, lz, left, right;
};

node tree[MAX_SIZE];
int cnt = 0;

int create(int l, int r) {
    ++cnt;
    tree[cnt].mn = l;
    tree[cnt].mx = r;
    return cnt;
}

void pushdown(int rt, int l, int r) {
    if (l > r) return;
    //if (tree[rt].lz != 0) {
    if (l != r) {
        if (!tree[rt].left) tree[rt].left = create(l, MID);
        if (!tree[rt].right) tree[rt].right = create(MID + 1, r);
        tree[tree[rt].left].lz += tree[rt].lz;
        tree[tree[rt].left].mn += tree[rt].lz;
        tree[tree[rt].left].mx += tree[rt].lz;
        tree[tree[rt].right].lz += tree[rt].lz;
        tree[tree[rt].right].mn += tree[rt].lz;
        tree[tree[rt].right].mx += tree[rt].lz;
    }

    tree[rt].lz = 0;
    //}
}

int update(int rt, int start, int end, int l, int r, int val) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(rt, l, r);

    if (start <= l && r <= end) {
        tree[rt].lz += val;
        tree[rt].mn += val;
        tree[rt].mx += val;
        return rt;
    }

    if (end <= MID) {
        tree[rt].left = update(tree[rt].left, start, end, l, MID, val);
    } else if (start >= MID + 1) {
        tree[rt].right = update(tree[rt].right, start, end, MID + 1, r, val);
    } else {
        tree[rt].left = update(tree[rt].left, start, end, l, MID, val);
        tree[rt].right = update(tree[rt].right, start, end, MID + 1, r, val);
    }

    tree[rt].mn = min(tree[tree[rt].left].mn, tree[tree[rt].right].mn);
    tree[rt].mx = max(tree[tree[rt].left].mx, tree[tree[rt].right].mx);
    return rt;
}

int query_min(int rt, int l, int r, int lim) {
    if (l > r) return -2;
    pushdown(rt, l, r);
    if (tree[rt].mn > lim) return -2;
    if (l == r) return l;
    if (tree[tree[rt].right].mn <= lim) return query_min(tree[rt].right, MID + 1, r, lim);
    return query_min(tree[rt].left, l, MID, lim);
}

int query_max(int rt, int l, int r, int lim) {
    if (l > r) return 1000000002;
    pushdown(rt, l, r);
    if (tree[rt].mx < lim) return 1000000002;
    if (l == r) return l;
    if (tree[tree[rt].left].mx >= lim) return query_max(tree[rt].left, l, MID, lim);
    return query_max(tree[rt].right, MID + 1, r, lim);
}

int query(int rt, int pos, int l, int r) {
    if (pos < l || pos > r || l > r) return 0;
    pushdown(rt, l, r);

    if (l == r) return tree[rt].mn;
    if (pos <= MID) return query(tree[rt].left, pos, l, MID);
    return query(tree[rt].right, pos, MID + 1, r);
}

int leftbound = 0, rightbound = 1000000001;

int main() {
    create(leftbound, rightbound);
    int N;
    scanf("%d", &N);
    int i, ans = 0;
    for (i = 1; i <= N; ++i) {
        int T, Q;
        scanf("%d", &T);
        int lft = query_min(1, leftbound, rightbound, T - 1);
        int rit = query_max(1, leftbound, rightbound, T + 1);
        update(1, leftbound, lft, leftbound, rightbound, 1);
        update(1, rit, rightbound, leftbound, rightbound, -1);
        scanf("%d", &Q);
        while (Q-- > 0) {
            int x;
            scanf("%d", &x);
            x = (x + ans) % rightbound;
            ans = query(1, x, leftbound, rightbound);
            printf("%d\n", ans);
        }
    }
    return 0;
}