#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
typedef long long ll;
using namespace std;
vector<int> f[MAX_SIZE];
vector<int> sz[MAX_SIZE];
// first -> second
vector<pair<int, int>> op;
vector<pair<int, int>> tree[MAX_SIZE * 8];
// each edge's last occurrence time
map<pair<int, int>, int> mp;
// queries, two end points of the edge
pair<int, int> q[MAX_SIZE];
vector<pair<int, int>> color[MAX_SIZE];
ll ans[MAX_SIZE * 4];
int N;

void update(int start, int end, int l, int r, int index, int v1, int v2) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].emplace_back(v1, v2);
        return;
    }
    if (end <= MID) {
        update(start, end, l, MID, LEFT, v1, v2);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v1, v2);
    } else {
        update(start, end, l, MID, LEFT, v1, v2);
        update(start, end, MID + 1, r, RIGHT, v1, v2);
    }
}

int find(int x) {
    if (x == f[x].back()) return x;
    return find(f[x].back());
}

void unionset(int v1, int v2) {
    int a = find(v1), b = find(v2);
    if (a == b) {
        op.emplace_back(-1, -1);
        return;
    }
    if (sz[a].back() > sz[b].back()) swap(a, b);
    f[a].push_back(b);
    sz[b].push_back(sz[a].back() + sz[b].back());
    op.emplace_back(a, b);
}

void del() {
    if (op.empty()) return;
    if (op.back().first == -1) {
        op.pop_back();
    } else {
        int v1 = op.back().first, v2 = op.back().second;
        op.pop_back();
        f[v1].pop_back();
        sz[v2].pop_back();
    }
}

void dfs(int l, int r, int index) {
    if (l > r) return;
    int cnt = 0;
    for (auto p : tree[index]) {
        unionset(p.first, p.second);
        ++cnt;
    }
    
    if (l == r) {
        if (q[l].first != 0) {
            ans[l] = 1ll * sz[find(q[l].first)].back() * sz[find(q[l].second)].back();
        }
        while (cnt-- > 0) del();
        return;
    }
    
    dfs(l, MID, LEFT);
    dfs(MID + 1, r, RIGHT);
    while (cnt-- > 0) del();
}

struct qrs {
    char tp;
    int u;
    int v;
};

vector<qrs> edgops; 

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        f[i].push_back(i);
        sz[i].push_back(1);
    }
    for (i = 1; i <= N - 1; ++i) {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        if (u > v) swap(u, v);
        color[x].emplace_back(u, v);   
        edgops.push_back(qrs{'+', u, v});
    }


    for (i = 1; i <= N; ++i) {
        for (auto p : color[i]) {
            edgops.push_back(qrs{'-', p.first, p.second});
        }

        for (auto p : color[i]) {
            edgops.push_back(qrs{'q', p.first, p.second});
        }

        for (auto p : color[i]) {
            edgops.push_back(qrs{'+', p.first, p.second});
        }
    }

    int qid = 0;
    for (auto qr : edgops) {
        if (qr.tp == '+') {
            mp[make_pair(qr.u, qr.v)] = qid + 1;
        } else if (qr.tp == '-') {
            debug("add edge <%d, %d> qid from %d to %d\n", qr.u, qr.v, mp[make_pair(qr.u, qr.v)], qid);
            update(mp[make_pair(qr.u, qr.v)], qid, 1, N - 1, 1, qr.u, qr.v);
            mp.erase(make_pair(qr.u, qr.v));
        } else {
            q[++qid].first = qr.u;
            q[qid].second = qr.v;
            debug("query %d edge is <%d,%d>\n", qid, qr.u, qr.v);
        }
    }

    for (auto p : mp) {
        debug("add edge <%d, %d> qid from %d to %d\n",  p.first.first, p.first.second, p.second, N - 1);
        update(p.second, N - 1, 1, N - 1, 1, p.first.first, p.first.second);
    }

    dfs(1, N - 1, 1);

    ll ret = 0;
    for (i = 1; i < N; ++i) {
        ret = ret + ans[i];
    }

    printf("%lld\n", ret);
    return 0;
}