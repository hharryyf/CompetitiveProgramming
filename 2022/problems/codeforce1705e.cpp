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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef long double ld;

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

struct segt {
    int lz, mn, mx;
};

segt tree[MAX_SIZE];

int maxR = 220011;

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = -1;
    if (l == r) return;
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != -1) {
        if (l != r) {
            tree[LEFT].mn = tree[LEFT].mx = tree[RIGHT].mn = tree[RIGHT].mx = tree[LEFT].lz = tree[RIGHT].lz = tree[index].lz;
        }
        tree[index].lz = -1;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz = tree[index].mx = tree[index].mn = val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }

    tree[index].mn = min(tree[LEFT].mn, tree[RIGHT].mn);
    tree[index].mx = max(tree[LEFT].mx, tree[RIGHT].mx);
}

int findLZero(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return maxR + 1;
    pushdown(l, r, index);
    if (tree[index].mn > 0) return maxR + 1;
    if (start <= l && r <= end) {
        if (l == r) return l;
        if (tree[LEFT].mn == 0) return findLZero(start, end, l, MID, LEFT);
        return findLZero(start, end, MID + 1, r, RIGHT);
    }

    if (end <= MID) return findLZero(start, end, l, MID, LEFT);
    if (start >= MID + 1) return findLZero(start, end, MID + 1, r, RIGHT);
    return min(findLZero(start, end, l, MID, LEFT),  findLZero(start, end, MID + 1, r, RIGHT));
}

int findLOne(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return maxR + 1;
    pushdown(l, r, index);
    if (tree[index].mx < 1) return maxR + 1;
    if (start <= l && r <= end) {
        if (l == r) return l;
        if (tree[LEFT].mx == 1) return findLOne(start, end, l, MID, LEFT);
        return findLOne(start, end, MID + 1, r, RIGHT);
    }

    if (end <= MID) return findLOne(start, end, l, MID, LEFT);
    if (start >= MID + 1) return findLOne(start, end, MID + 1, r, RIGHT);
    return min(findLOne(start, end, l, MID, LEFT),  findLOne(start, end, MID + 1, r, RIGHT));
}

int findROne(int l, int r, int index) {
    if (l > r) return -1;
    pushdown(l, r, index);
    if (tree[index].mx < 1) return -1;
    if (l == r) return l;
    if (tree[RIGHT].mx >= 1) return findROne(MID + 1, r, RIGHT);
    return findROne(l, MID, LEFT);
}

// we want to add (1 << pos)
void add(int pos) {
    // find the position p of the leftmost 0 that is in range [pos, maxn]
    // set the position to be 1
    // and all position from [pos, p-1] to be 0
    int p = findLZero(pos, maxR, 1, maxR, 1);
    update(p, p, 1, maxR, 1, 1);
    update(pos, p - 1, 1, maxR, 1, 0);
}

// we want to subtract (1 << pos)
void subtract(int pos) {
    // find the position p of the leftmost 1 that is in range [pos, maxn]
    // set that position to be 0
    // and all position from [pos, p-1] to be 1
    int p = findLOne(pos, maxR, 1, maxR, 1);
    update(p, p, 1, maxR, 1, 0);
    update(pos, p - 1, 1, maxR, 1, 1);
}

int query() {
    // find the position of the right most position that is 1
    return findROne(1, maxR, 1);
}

int a[MAX_SIZE];

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    int i;
    build(1, maxR, 1);
    for (i = 1 ; i <= N; ++i) {
        scanf("%d", &a[i]);
        add(a[i]);
    }

    while (Q-- > 0) {
        int k, l;
        scanf("%d%d", &k, &l);
        add(l);
        subtract(a[k]);
        a[k] = l;
        printf("%d\n", query());
    }
    return 0;
}