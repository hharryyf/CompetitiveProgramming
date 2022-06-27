#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 524312
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

struct segt {
    ll rmax, rmin;
};

segt tree[MAX_SIZE];

ll pre[MAX_SIZE], a[MAX_SIZE], b[MAX_SIZE];
int N, Q;

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.rmax = max(t1.rmax, t2.rmax);
    ret.rmin = min(t1.rmin, t2.rmin);
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].rmax = tree[index].rmin = pre[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

const ll inf = 1e18;

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return {-inf, inf};
    if (start <= l && r <= end) {
        return tree[index];
    }

    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}


int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
    for (i = 1; i <= N; ++i) scanf("%lld", &b[i]);
    for (i = 1; i <= N; ++i) pre[i] = pre[i-1] - a[i] + b[i];
    build(1, N, 1);
    while (Q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto rt = query(l, r, 1, N, 1);
        if (pre[r] - pre[l-1] == 0 && rt.rmin - pre[l-1] >= 0) {
            printf("%lld\n", rt.rmax - pre[l-1]);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}