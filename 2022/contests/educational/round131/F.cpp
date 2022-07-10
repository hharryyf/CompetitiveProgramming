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
const int inf32 = 19260817;
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

struct Vector {
    array<ll, 3> a;
    Vector operator + (Vector other) {
        Vector ret;
        int i;
        for (i = 0 ; i < 3; ++i) {
            ret.a[i] = 0;
        }

        for (i = 0 ; i < 3; ++i) {
            ret.a[i] = a[i] + other.a[i];
        }

        return ret;
    }
};

struct Matrix {
    array<array<ll, 3>, 3> a;

    Vector operator *(Vector &other) {
        Vector ret;
        int i, j;
        for (i = 0 ; i < 3; ++i) {
            ret.a[i] = 0;
        }

        for (i = 0 ; i < 3; ++i) {
            for (j = 0 ; j < 3; ++j) {
                ret.a[i] += a[i][j] * other.a[j];
            }
        }
        return ret;
    }

    Matrix operator *(Matrix &other) {
        Matrix ret;
        int i, j, k;
        for (i = 0 ; i < 3; ++i) {
            for (j = 0 ; j < 3; ++j) {
                ret.a[i][j] = 0;
            }
        }

        for (i = 0 ; i < 3; ++i) {
            for (j = 0 ; j < 3; ++j) {
                for (k = 0; k < 3; ++k) {
                    ret.a[i][j] += a[i][k] * other.a[k][j];
                }
            }
        }
        return ret;
    }
};

Matrix I, Up, Down;
Vector Zero, One;

void init() {
    int i, j;
    for (i = 0 ; i < 3; ++i) {
        for (j = 0 ; j < 3; ++j) {
            if (i == j) {
                I.a[i][j] = 1;
            } else {
                I.a[i][j] = 0;
            }
            Up.a[i][j] = 0;
            Down.a[i][j] = 0;
        }
    }

    for (i = 0 ; i < 3; ++i) {
        Zero.a[i] = 0;
        One.a[i] = 0;
        if (i == 0) {
            One.a[i] = 1;
        }
    }

    Up.a[0][0] = 1;
    Up.a[1][0] = 1, Up.a[1][1] = 1;
    Up.a[2][0] = 1, Up.a[2][1] = 2, Up.a[2][2] = 1;
    Down.a[0][0] = 1;
    Down.a[1][0] = -1, Down.a[1][1] = 1;
    Down.a[2][0] = 1, Down.a[2][1] = -2, Down.a[2][2] = 1;
}

struct segt {
    Vector vc;
    Matrix lz;
    bool exist;
};

segt tree[MAX_SIZE];

Vector query(int index) {
    if (tree[index].exist) return tree[index].vc;
    return Zero;
}

void pullup(int index) {
    tree[index].vc = query(LEFT) + query(RIGHT);
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (l != r) {
        tree[LEFT].lz = tree[LEFT].lz * tree[index].lz;
        tree[RIGHT].lz = tree[RIGHT].lz * tree[index].lz;
        tree[LEFT].vc =  tree[index].lz * tree[LEFT].vc;
        tree[RIGHT].vc = tree[index].lz * tree[RIGHT].vc;
    }

    tree[index].lz = I;
}

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = I;
    tree[index].exist = true;
    if (l == r) {
        tree[index].exist = false;
        tree[index].vc = One;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    pullup(index);
}

void update(int start, int end, int l, int r, int index, bool up) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        if (up) {
            tree[index].lz = Up;
            tree[index].vc = Up * tree[index].vc;
        } else {
            tree[index].lz = Down;
            tree[index].vc = Down * tree[index].vc;
        }
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, up);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, up);
    } else {
        update(start, end, l, MID, LEFT, up);
        update(start, end, MID + 1, r, RIGHT, up);
    }

    pullup(index);
}

void updatept(int pt, int l, int r, int index, bool up) {
    if (pt < l || pt > r || l > r) return;
    pushdown(l, r, index);
    if (l == r) {
        tree[index].exist = up;
        return;
    }

    if (pt <= MID) {
        updatept(pt, l, MID, LEFT, up);
    } else {
        updatept(pt, MID + 1, r, RIGHT, up);
    }

    pullup(index);
}

int ok[MAX_SIZE];

int main() {
    init();
    int Q, d;
    int maxd = 200000;
    scanf("%d%d", &Q, &d);
    build(1, maxd, 1);
    while (Q-- > 0) {
        int x;
        scanf("%d", &x);
        ok[x] ^= 1;
        update(max(1, x - d), x, 1, maxd, 1, ok[x]);
        updatept(x, 1, maxd, 1, ok[x]);
        auto vc = query(1);
        vc = Down * vc;
        debug("%lld %lld %lld\n", vc.a[0], vc.a[1], vc.a[2]);
        printf("%lld\n", (vc.a[2] - vc.a[1]) / 2);
    }
    return 0;
}