#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;

struct segt {
    int rmin, mcnt, rsec;
    int cnt[30];
};

int a[MAX_SIZE];
segt tree[MAX_SIZE];
int N, Q;

void upd(int index, int val) {
    int i;
    for (i = 0 ; i < 30; ++i) {
        tree[index].cnt[i] -= ((tree[index].rmin >> i) & 1) * tree[index].mcnt;
    }
    tree[index].rmin = val;
    for (i = 0 ; i < 30; ++i) {
        tree[index].cnt[i] += ((tree[index].rmin >> i) & 1) * tree[index].mcnt;
    }
}

void pushdown(int l, int r, int index) {
    if (l >= r) return;
    if (tree[index].rmin > tree[LEFT].rmin) {
        upd(LEFT, tree[index].rmin);
    }

    if (tree[index].rmin > tree[RIGHT].rmin) {
        upd(RIGHT, tree[index].rmin);
    }
}

void pullup(int index) {
    int i;
    for (i = 0; i < 30; ++i) {
        tree[index].cnt[i] = tree[LEFT].cnt[i] + tree[RIGHT].cnt[i];
    }

    if (tree[LEFT].rmin > tree[RIGHT].rmin) {
        tree[index].rmin = tree[RIGHT].rmin;
        tree[index].mcnt = tree[RIGHT].mcnt;
        tree[index].rsec = min(tree[RIGHT].rsec, tree[LEFT].rmin);
    } else if (tree[LEFT].rmin == tree[RIGHT].rmin) {
        tree[index].rmin = tree[LEFT].rmin;
        tree[index].rsec = min(tree[LEFT].rsec, tree[RIGHT].rsec);
        tree[index].mcnt = tree[LEFT].mcnt + tree[RIGHT].mcnt;
    } else {
        tree[index].rmin = tree[LEFT].rmin;
        tree[index].mcnt = tree[LEFT].mcnt;
        tree[index].rsec = min(tree[LEFT].rsec, tree[RIGHT].rmin);
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r) return;
    if (val <= tree[index].rmin) return;
    pushdown(l, r, index);
    if (start <= l && r <= end && tree[index].rsec > val) {
        upd(index, val);
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

    pullup(index);
}

int queryxor(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        int ret = 0, i;
        for (i = 0 ; i < 30; ++i) {
            ret ^= (tree[index].cnt[i] & 1) << i;
        }
        return ret;
    }

    int ret = 0;
    if (end <= MID) {
        ret = queryxor(start, end, l, MID, LEFT);

    } else if (start >= MID + 1) {
        ret = queryxor(start, end, MID + 1, r, RIGHT);
    } else {
        ret = queryxor(start, end, l, MID, LEFT) ^ queryxor(start, end, MID + 1, r, RIGHT);
    }

    pullup(index);

    return ret;
}

int querybit(int start, int end, int l, int r, int index, int id) {
    if (start > end || l > r || start > r || l > end) return 0;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        return tree[index].cnt[id];
    }

    int ret = 0;
    if (end <= MID) {
        ret = querybit(start, end, l, MID, LEFT, id);

    } else if (start >= MID + 1) {
        ret = querybit(start, end, MID + 1, r, RIGHT, id);
    } else {
        ret = querybit(start, end, l, MID, LEFT, id) + querybit(start, end, MID + 1, r, RIGHT, id);
    }

    pullup(index);

    return ret;
}

int getans(int l, int r, int val) {
    int xx = queryxor(l, r, 1, N, 1);
    if ((xx ^ val) == 0) return 0;
    int i, idx = 0;
    for (i = 29; i >= 0; --i) {
        if (((xx ^ val) >> i) & 1) {
            idx = i;
            break;
        }
    }

    return querybit(l, r, 1, N, 1, idx) + ((val >> idx) & 1);
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].mcnt = 1;
        tree[index].rsec = (1 << 30);
        tree[index].rmin = a[l];
        int i;
        for (i = 0 ; i < 30; ++i) {
            tree[index].cnt[i] += ((a[l] >> i) & 1);
        }

        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    pullup(index);
}


int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    build(1, N, 1);

    while (Q-- > 0) {
        int op, l, r, x;
        scanf("%d%d%d%d", &op, &l, &r, &x);
        if (op == 1) {
            update(l, r, 1, N, 1, x);           
        } else {
            printf("%d\n", getans(l, r, x));
        }
    }
    return 0;
}