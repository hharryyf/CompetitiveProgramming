#include <bits/stdc++.h>
#define MAX_SIZE 65677
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

vector<int> g[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], son[MAX_SIZE], parent[MAX_SIZE];
int top[MAX_SIZE], depth[MAX_SIZE], sz[MAX_SIZE], cnt = 0;
int N;


struct rangetree {
    struct segt {
        int lz, rmax, rcnt;
    };

    segt tree[MAX_SIZE];

    segt pullup(segt t1, segt t2) {
        segt ret;
        ret.lz = 0;
        ret.rmax = max(t1.rmax, t2.rmax);
        ret.rcnt = (ret.rmax == t1.rmax) * t1.rcnt + (ret.rmax == t2.rmax) * t2.rcnt;
        return ret;
    }

    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != 0) {
            if (l != r) {
                tree[LEFT].lz += tree[index].lz;
                tree[RIGHT].lz += tree[index].lz;
                tree[LEFT].rmax += tree[index].lz;
                tree[RIGHT].rmax += tree[index].lz;
            }

            tree[index].lz = 0;
        }
    }

    void build(int l, int r, int index) {
        if (l > r) return;
        tree[index].lz = 0;
        if (l == r) {
            tree[index].rcnt = 1;
            tree[index].rmax = 0;
            return;
        }

        build(l, MID, LEFT);
        build(MID + 1, r, RIGHT);
        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            tree[index].rmax += val;
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

        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    } 
    

    int query(int K) {
        return tree[1].rmax == K ? tree[1].rcnt : 0;
    }
};


rangetree tree;

void init() {
    tree.build(1, N, 1);
    for (int i = 0 ; i < MAX_SIZE; ++i) g[i].clear();
    memset(id, 0, sizeof(id));
    memset(rid, 0, sizeof(rid));
    memset(son, 0, sizeof(son));
    memset(parent, 0, sizeof(parent));
    memset(top, 0, sizeof(top));
    memset(depth, 0, sizeof(depth));
    memset(sz, 0, sizeof(sz));
    cnt = 0;
}


void dfs1(int v, int pre) {
    parent[v] = pre;
    depth[v] = depth[pre] + 1;
    sz[v] = 1;
    int max_subsz = 0;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs1(nv, v);
            sz[v] += sz[nv];
            if (max_subsz < sz[nv]) {
                son[v] = nv, max_subsz = sz[nv];
            }
        }
    }
}

void dfs2(int v, int tp) {
    top[v] = tp, id[v] = ++cnt, rid[id[v]] = v;
    if (son[v]) {
        dfs2(son[v], tp);
    }

    for (auto nv : g[v]) {
        if (nv != parent[v] && nv != son[v]) {
            dfs2(nv, nv);
        }
    }
}

void hld(int x, int y, int v) {
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (depth[fx] >= depth[fy]) {
            tree.update(id[fx], id[x], 1, N, 1, v);
            x = parent[fx], fx = top[x];
        } else {
            tree.update(id[fy], id[y], 1, N, 1, v);
            y = parent[fy], fy = top[y];
        }
    }

    if (id[x] <= id[y]) {
        tree.update(id[x], id[y], 1, N, 1, v);
    } else {
        tree.update(id[y], id[x], 1, N, 1, v);
    }
}



void solve() {
    int Q, K, i;
    scanf("%d", &N);
    init();
    for (i = 1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    scanf("%d", &Q);
    while (Q-- > 0) {
        scanf("%d", &K);
        vector<pair<int, int>> curr;
        for (i = 1; i <= K; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            curr.emplace_back(u, v);
            hld(u, v, 1);
        }

        printf("%d\n", tree.query(K));
        for (auto v : curr) {
            hld(v.first, v.second, -1);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case %d:\n", t);
        solve();
    }
    return 0;
}