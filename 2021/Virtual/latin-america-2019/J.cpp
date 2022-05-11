#include <bits/stdc++.h>
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

const int inf = 1e9 + 7;
int tree[MAX_SIZE], h[MAX_SIZE];
int N, Q;

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = h[l];
        return;
    } 

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || pt > r || l > r) return;
    if (l == r) {
        tree[index] = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) {
        return -inf;
    }

    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

// tp = 1, find the leftmost position in range [start, end] > val
// tp = 0, find the rightmost position in range [start, end] > val
int findpos(int start, int end, int l, int r, int index, int val, int tp) {
    if (start > end || l > r || start > r || l > end) {
        if (tp == 1) return inf;
        return -inf;
    }

    if (start <= l && r <= end) {
        if (tree[index] <= val) {
            if (tp == 1) return inf;
            return -inf;
        }
        if (l == r) return l;
        if (tp == 1) {
            if (tree[LEFT] > val) {
                return findpos(start, end, l, MID, LEFT, val, tp);
            }
            return findpos(start, end, MID + 1, r, RIGHT, val, tp);
        } else {
            if (tree[RIGHT] > val) {
                return findpos(start, end, MID + 1, r, RIGHT, val, tp); 
            }
            return findpos(start, end, l, MID, LEFT, val, tp);
        }
    }

    if (end <= MID) return findpos(start, end, l, MID, LEFT, val, tp);
    if (start >= MID + 1) return findpos(start, end, MID + 1, r, RIGHT, val, tp);
    if (tp) {
        return min(findpos(start, end, l, MID, LEFT, val, tp), findpos(start, end, MID + 1, r, RIGHT, val, tp));
    }
    return max(findpos(start, end, l, MID, LEFT, val, tp), findpos(start, end, MID + 1, r, RIGHT, val, tp));
}

char s[4];

int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &h[i]);
    }

    build(1, N, 1);
    for (i = 1; i <= Q; ++i) {
        int v, u;
        scanf("%s%d", s, &v);
        if (s[0] == 'L') {
            int maxl = query(1, v - 1, 1, N, 1), maxr = query(v + 1, N, 1, N, 1);
            int lpos, rpos;
            if (maxl < h[v]) {
                printf("%d\n", v);
                continue;
            }

            if (maxr < h[v]) {
                lpos = findpos(1, v - 1, 1, N, 1, h[v], 0);
                printf("%d\n", lpos);
                continue;
            }

            if (maxl < maxr) {
                rpos = findpos(v + 1, N, 1, N, 1, maxl, 1);
                printf("%d\n", rpos);
            } else {
                lpos = findpos(1, v - 1, 1, N, 1, maxr, 0);
                printf("%d\n", lpos);
            }
        } else if (s[0] == 'R') {
            int maxl = query(1, v - 1, 1, N, 1), maxr = query(v + 1, N, 1, N, 1);
            int lpos, rpos;
            if (maxr < h[v]) {
                printf("%d\n", v);
                continue;
            }

            if (maxl < h[v]) {
                lpos = findpos(v + 1, N, 1, N, 1, h[v], 1);
                printf("%d\n", lpos);
                continue;
            }

            if (maxl < maxr) {
                rpos = findpos(v + 1, N, 1, N, 1, maxl, 1);
                printf("%d\n", rpos);
            } else {
                lpos = findpos(1, v - 1, 1, N, 1, maxr, 0);
                printf("%d\n", lpos);
            }
        } else {
            scanf("%d", &u);
            h[v] = u;
            update(v, 1, N, 1, u);
        }
    }
    return 0;
}