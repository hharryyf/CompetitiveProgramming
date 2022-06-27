#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
typedef long long ll;

int a[MAX_SIZE];

struct segt {
    ll sm, lz;
};

segt tree[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].sm = a[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index].sm = tree[LEFT].sm + tree[RIGHT].sm;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].lz = tree[index].lz;
            tree[RIGHT].lz = tree[index].lz;
            tree[LEFT].sm =1ll * (MID - l + 1) * tree[index].lz;
            tree[RIGHT].sm = 1ll * (r - MID) * tree[index].lz;
        }

        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].sm = val * (r - l + 1);
        tree[index].lz = val;
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
    tree[index].sm = tree[LEFT].sm + tree[RIGHT].sm;
}



int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) scanf("%d", &a[i]);
    build(1, N, 1);
    while (Q-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int id, v;
            scanf("%d%d", &id, &v);
            update(id, id, 1, N, 1, v);
        } else {
            int v;
            scanf("%d", &v);
            update(1, N, 1, N, 1, v);
        }
        printf("%lld\n", tree[1].sm);
    }

    
    return 0;
}