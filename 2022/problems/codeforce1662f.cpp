#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
typedef long long ll;
#define MAX_SIZE 524312
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

const int INF = 1e9;

struct rangemax_tree {
    pair<int, int> tree[MAX_SIZE];
    
    pair<int, int> pullup(pair<int, int> t1, pair<int, int> t2) {
        pair<int, int> ret;
        ret.first = max(t1.first, t2.first);
        if (ret.first == t1.first) {
            ret.second = t1.second;
        } else {
            ret.second = t2.second;
        }
        return ret;
    }
    
    void build(int l, int r, int index, int val) {
        if (l > r) return;
        if (l == r) {
            tree[index].first = val;
            tree[index].second = l;
            return;
        }

        build(l, MID, LEFT, val);
        build(MID + 1, r, RIGHT, val);
        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    void update(int pt, int l, int r, int index, int val) {
        if (pt < l || pt > r || l > r) return;
        if (l == r) {
            tree[index].first = val;
            return;
        }

        if (pt <= MID) {
            update(pt, l, MID, LEFT, val);
        } else {
            update(pt, MID + 1, r, RIGHT, val);
        }

        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    pair<int, int> query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) {
            return make_pair(-INF, 0);
        }

        if (start <= l && r <= end) return tree[index];
        if (end <= MID) return query(start, end, l, MID, LEFT);
        if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
        return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};


struct rangemin_tree {
    pair<int, int> tree[MAX_SIZE];
    
    pair<int, int> pullup(pair<int, int> t1, pair<int, int> t2) {
        pair<int, int> ret;
        ret.first = min(t1.first, t2.first);
        if (ret.first == t1.first) {
            ret.second = t1.second;
        } else {
            ret.second = t2.second;
        }
        return ret;
    }
    
    void build(int l, int r, int index, int val) {
        if (l > r) return;
        if (l == r) {
            tree[index].first = val;
            tree[index].second = l;
            return;
        }

        build(l, MID, LEFT, val);
        build(MID + 1, r, RIGHT, val);
        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    void update(int pt, int l, int r, int index, int val) {
        if (pt < l || pt > r || l > r) return;
        if (l == r) {
            tree[index].first = val;
            return;
        }

        if (pt <= MID) {
            update(pt, l, MID, LEFT, val);
        } else {
            update(pt, MID + 1, r, RIGHT, val);
        }

        tree[index] = pullup(tree[LEFT], tree[RIGHT]);
    }

    pair<int, int> query(int start, int end, int l, int r, int index) {
        if (start > end || l > r || start > r || l > end) {
            return make_pair(INF, 0);
        }

        if (start <= l && r <= end) return tree[index];
        if (end <= MID) return query(start, end, l, MID, LEFT);
        if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
        return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
    }
};

rangemax_tree maxt;
rangemin_tree mint;

int N, A, B;
int p[MAX_SIZE], dist[MAX_SIZE];

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d", &N, &A, &B);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &p[i]);
            dist[i] = INF;
        }
        
        maxt.build(1, N, 1, -INF);
        mint.build(1, N, 1, INF);

        for (i = 1; i <= N; ++i) {
            maxt.update(i, 1, N, 1, i + p[i]);
            mint.update(i, 1, N, 1, i - p[i]);
        }

        queue<int> q;
        q.push(A);
        dist[A] = 0;
        maxt.update(A, 1, N, 1, -INF);
        mint.update(A, 1, N, 1, INF);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            // right side
            while (true) {
                auto nxt = mint.query(v, min(v + p[v], N), 1, N, 1);
                if (nxt.first > v) break;
                dist[nxt.second] = min(dist[nxt.second], dist[v] + 1);
                mint.update(nxt.second, 1, N, 1, INF);
                maxt.update(nxt.second, 1, N, 1, -INF);
                q.push(nxt.second);
            }
            // left side
            while (true) {
                auto nxt = maxt.query(max(v - p[v], 1), v, 1, N, 1);
                if (nxt.first < v) break;
                dist[nxt.second] = min(dist[nxt.second], dist[v] + 1);
                q.push(nxt.second);
                maxt.update(nxt.second, 1, N, 1, -INF);
                mint.update(nxt.second, 1, N, 1, INF);
            }
        }

        printf("%d\n", dist[B]);
    }
    return 0;
}