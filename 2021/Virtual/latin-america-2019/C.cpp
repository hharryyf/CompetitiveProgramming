#include <bits/stdc++.h>
#define MAX_SIZE 524312
typedef long long ll;
using namespace std;
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
ll rmin[MAX_SIZE], rmax[MAX_SIZE], pre[MAX_SIZE];
int parent[MAX_SIZE][19];
int getidx(int v) { return v / 2;}
int getlow(int v) { return v * 2;}
int gethigh(int v) { return v * 2 + 1;}
ll getpre(int l, int r) { if (l > r) return 0; return pre[r] - pre[l-1];}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        rmin[index] = rmax[index] = pre[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    rmin[index] = min(rmin[LEFT], rmin[RIGHT]);
    rmax[index] = max(rmax[LEFT], rmax[RIGHT]);
}
// tp = 1 means query first < val
// tp = 0 means query first > val
int query(int start, int end, int l, int r, int index, ll val, int tp) {
    if (start > end || l > r || start > r || l > end) return MAX_SIZE;
    if (start <= l && r <= end) {
        if (tp == 1) {
            if (rmin[index] >= val) return MAX_SIZE;
            if (l == r) return l;
            if (rmin[LEFT] < val) return query(start, end, l, MID, LEFT, val, tp);
            return query(start, end, MID + 1, r, RIGHT, val, tp);
        } else {
            if (rmax[index] <= val) return MAX_SIZE;
            if (l == r) return l;
            if (rmax[LEFT] > val) return query(start, end, l, MID, LEFT, val, tp);
            return query(start, end, MID + 1, r, RIGHT, val, tp);
        }
    }

    if (end <= MID) return query(start, end, l, MID, LEFT, val, tp);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT, val, tp);
    return min(query(start, end, l, MID, LEFT, val, tp), query(start, end, MID + 1, r, RIGHT, val, tp));
}

int N, Q;
ll L, U;

int go(int id, int r) {
    int i;
    for (i = 18; i >= 0; --i) {
        if (parent[id][i] != 0 && parent[id][i] <= 2 * r + 1) {
            id = parent[id][i];
        }
    }
    return id;
}

void fix(ll &w) {
    if (w < L) w = L;
    if (w > U) w = U;
}

int main() {
    int i;
    scanf("%d%lld%lld", &N, &L, &U);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &pre[i]);
        pre[i] += pre[i-1];
    }

    build(1, N, 1);
    if (L != U) {
        for (i = N; i >= 1; --i) {
            int l = query(i, N, 1, N, 1, pre[i - 1], 1) + 1, r = query(i, N, 1, N, 1, U - L + pre[i-1], 0) + 1;
            int id = min(l, r);
            if (id <= N) {
                if (id == l) {
                    parent[getlow(i)][0] = getlow(id);
                } else {
                    parent[getlow(i)][0] = gethigh(id);
                }
            }

            l = query(i, N, 1, N, 1, L - U + pre[i -  1], 1) + 1, r = query(i, N, 1, N, 1, pre[i-1], 0) + 1;
            id = min(l, r);
            if (id <= N) {
                if (id == l) {
                    parent[gethigh(i)][0] = getlow(id);
                } else {
                    parent[gethigh(i)][0] = gethigh(id);
                }
            }

            for (l = 1; l <= 18; ++l) {
                parent[getlow(i)][l] = parent[parent[getlow(i)][l-1]][l-1];
                parent[gethigh(i)][l] = parent[parent[gethigh(i)][l-1]][l-1];
            }
        }
    }

    scanf("%d", &Q);
    while (Q-- > 0) {
        int l, r;
        ll w;
        scanf("%d%d%lld", &l, &r, &w);
        if (L == U) {
            printf("%lld\n", L);
            continue;
        }

        int ql = query(l, r, 1, N, 1, L + pre[l - 1] - w, 1) + 1, qr = query(l, r, 1, N, 1, pre[l-1] + U - w, 0) + 1;
        int id = min(ql, qr);
        if (id <= r) {
            //printf("the first id is %d ", id);
            w = w + getpre(l, id - 1);
            fix(w);
            if (id == ql) {
                id = getlow(id);
            } else {
                id = gethigh(id);
            }
            id = go(id, r);
            //printf(" the final id is %d ", id);
            if (id % 2 == 1) {
                w = U;
            } else {
                w = L;
            }
            w = w + getpre(getidx(id), r);
            fix(w);
            //printf("the answer is ");
            printf("%lld\n", w);
        } else {
            w = getpre(l, r) + w;
            fix(w);
            printf("%lld\n", w);
        }
    }
    return 0;
}