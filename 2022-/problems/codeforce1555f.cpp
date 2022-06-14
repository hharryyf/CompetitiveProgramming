#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1048597
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

const int mod = 1e9 + 7;

vector<int> g[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], son[MAX_SIZE], parent[MAX_SIZE];
int top[MAX_SIZE], depth[MAX_SIZE], sz[MAX_SIZE], cnt = 0;
int N;
 
 
struct rangetree {
    struct segt {
        int lz, rmax, rsum;
    };
 
    segt tree[MAX_SIZE];
 
    segt pullup(segt t1, segt t2) {
        segt ret;
        ret.lz = 0;
        ret.rmax = max(t1.rmax, t2.rmax);
        ret.rsum = t1.rsum + t2.rsum;
        return ret;
    }
 
    void pushdown(int l, int r, int index) {
        if (l > r) return;
        if (tree[index].lz != 0) {
            if (l != r) {
                tree[LEFT].lz = tree[index].lz;
                tree[RIGHT].lz = tree[index].lz;
                tree[LEFT].rmax = tree[index].lz;
                tree[RIGHT].rmax = tree[index].lz;
            }
 
            tree[index].lz = 0;
        }
    }
 
    void update(int start, int end, int l, int r, int index, int val) {
        if (start > end || l > r || start > r || l > end) return;
        pushdown(l, r, index);
        if (start <= l && r <= end) {
            // val = 1 means we set the value rmax to 1
            if (val == 1) {
                tree[index].rmax = 1;
                tree[index].lz = 1;
            } else {
                // it is guarenteed if we reach this query, we are getting start == end
                tree[index].rsum = 1;
            }
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
    
 
    segt query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) return tree[0];
        pushdown(l, r, index);
        if (start <= l && r <= end) return tree[index];
        if (end <= MID) return query(start, end, l, MID, LEFT);
        if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
        return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};
 
 
rangetree tree;

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

// change x --> y to value v
// if v = 1 we change rmax to 1
// if v = -1 we change rsum to 1
void change(int x, int y, int v) {
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
    
    if (x == y) return;
    if (id[x] <= id[y]) {
        tree.update(id[son[x]], id[y], 1, N, 1, v);
    } else {
        tree.update(id[son[y]], id[x], 1, N, 1, v);
    }
}

pair<int, int> hld(int x, int y) {
    pair<int, int> ret = {0, 0};
    int fx = top[x], fy = top[y];
    while (fx != fy) {
        if (depth[fx] >= depth[fy]) {
            auto curr = tree.query(id[fx], id[x], 1, N, 1);
            ret.first = max(ret.first, curr.rmax);
            ret.second = ret.second + curr.rsum;
            x = parent[fx], fx = top[x];
        } else {
            auto curr = tree.query(id[fy], id[y], 1, N, 1);
            ret.first = max(ret.first, curr.rmax);
            ret.second = ret.second + curr.rsum;
            y = parent[fy], fy = top[y];
        }
    }
    
    if (x == y) return ret;
    if (id[x] <= id[y]) {
        auto curr = tree.query(id[son[x]], id[y], 1, N, 1);
        ret.first = max(ret.first, curr.rmax);
        ret.second = ret.second + curr.rsum;
    } else {
        auto curr = tree.query(id[son[y]], id[x], 1, N, 1);
        ret.first = max(ret.first, curr.rmax);
        ret.second = ret.second + curr.rsum;
    }
    
    return ret;
}

array<int, 4> q[MAX_SIZE];
int f[MAX_SIZE], Q;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        f[fx] = fy;
    }
}

int main() {
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) f[i] = i;
    for (i = 1; i <= Q; ++i) {
        scanf("%d%d%d", &q[i][0], &q[i][1], &q[i][2]);
        if (find(q[i][0]) != find(q[i][1])) {
            unionset(q[i][0], q[i][1]);
            g[q[i][0]].push_back(q[i][1]);
            g[q[i][1]].push_back(q[i][0]);
            q[i][3] = 1;
        } else {
            q[i][3] = 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (find(i) == i) {
            dfs1(i, 0);
            dfs2(i, i);
        }
    }

    for (i = 1; i <= Q; ++i) {
        if (!q[i][3]) {
            auto ret = hld(q[i][0], q[i][1]);
            if (ret.first == 0) {
                if ((ret.second & 1) != q[i][2]) {
                    q[i][3] = 1;
                    change(q[i][0], q[i][1], 1);
                }
            }
        } else {
            if (q[i][2]) {
                change(q[i][0], q[i][1], -1);
            }
        }
    }

    for (i = 1; i <= Q; ++i) {
        printf("%s\n", q[i][3] ? "YES" : "NO");
    }
    return 0;
}