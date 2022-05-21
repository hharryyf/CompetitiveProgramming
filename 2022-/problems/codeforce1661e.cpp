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

using namespace std;

struct segt {
    int sz;
    int L[3], R[3];
};

int N;

char st[3][MAX_SIZE];
segt tree[MAX_SIZE];

vector<int> f(MAX_SIZE * 2);

int find(vector<int> &f, int x) {
    if (f[x] == x) return x;
    return f[x] = find(f, f[x]);
}

void unionset(vector<int> &f, int x, int y) {
    int a = find(f, x);
    int b = find(f, y);
    f[a] = b;
}

void print(segt &t) {
    debug("component l=%d r=%d sz=%d L[0]=%d L[1]=%d L[2]=%d R[0]=%d R[1]=%d R[2]=%d\n", t.l, t.r, t.sz, t.L[0], t.L[1], t.L[2], t.R[0], t.R[1], t.R[2]);
}


segt pullup(segt tl, segt tr, int l, int r) {
    segt ret;
    int i;
    for (i = 0 ; i < 3; ++i) ret.L[i] = ret.R[i] = 0;
    debug("merge\n");
    print(tl);
    print(tr);
    ret.sz = tl.sz + tr.sz;
    for (i = 0 ; i < 3; ++i) {
        if (tl.L[i] != 0) {
            f[tl.L[i]] = tl.L[i];
        }

        if (tl.R[i] != 0) {
            f[tl.R[i]] = tl.R[i];
        }

        if (tr.L[i] != 0) {
            f[tr.L[i]] = tr.L[i];
        }

        if (tr.R[i] != 0) {
            f[tr.R[i]] = tr.R[i];
        }
    }
    for (i = 0 ; i < 3; ++i) {
        if (st[i][l] == st[i][r] && st[i][l] == '1') {
            if (find(f, tl.R[i]) != find(f, tr.L[i])) {
                unionset(f, tl.R[i], tr.L[i]);
                ret.sz--;
            }
        }
    }

    for (i = 0 ; i < 3; ++i) {
        if (tl.L[i] != 0) {
            ret.L[i] = find(f, tl.L[i]);
        }

        if (tr.R[i] != 0) {
            ret.R[i] = find(f, tr.R[i]);
        }
    }

    debug("get");
    print(ret);
    
    return ret;
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        if (st[0][l] == '1') {
            tree[index].L[0] = tree[index].R[0] = l * 3;
            tree[index].sz += 1;
        }

        if (st[1][l] == '1') {
            tree[index].L[1] = tree[index].R[1] = l * 3 + 1;
            tree[index].sz += 1;
        }

        if (st[2][l] == '1') {
            tree[index].L[2] = tree[index].R[2] = l * 3 + 2;
            tree[index].sz += 1;
        }

        if (st[0][l] == '1' && st[1][l] == '1') {
            tree[index].L[1] = tree[index].R[1] = tree[index].L[0] = tree[index].R[0];
            tree[index].sz -= 1;
        }

        if (st[1][l] == '1' && st[2][l] == '1') {
            tree[index].L[2] = tree[index].R[2] = tree[index].L[1] = tree[index].R[1];
            tree[index].sz -= 1;
        }
        return;
    }   

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT], MID, MID + 1);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT), MID, MID + 1);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0; i < 3; ++i) {
        scanf("%s", st[i] + 1);
    }

    build(1, N, 1);

    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r, 1, N, 1).sz);
    }
    return 0;
}