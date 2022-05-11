#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 511
struct edges {
    int from, to;
    ll cost;
    bool operator < (edges other) const {
        return cost < other.cost;
    }
};

int f[MAX_SIZE], N;
ll sz[MAX_SIZE];
vector<edges> edg1;
vector<edges> edg2;

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

ll query(int x) {
    return sz[find(x)]; 
}

void unionset(int x, int y, ll cost) {
    int a = find(x), b = find(y);
    f[a] = b;
    sz[b] += sz[a];
    sz[b] += cost;
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) f[i] = i;

    for (i = 2; i <= N; ++i) {
        for (j = 1; j < i; ++j) {
            ll v;
            scanf("%lld", &v);
            if (v < 0) {
                edg1.push_back(edges{i, j, -v});
            } else if (v > 0) {
                edg2.push_back(edges{i, j, v});
            }
        }
    }

    sort(edg1.begin(), edg1.end());

    for (auto e : edg1) {
        if (find(e.from) != find(e.to)) {
            unionset(e.from, e.to, e.cost);
        }
    }

    for (auto &e : edg2) {
        e.cost += query(e.from) + query(e.to);
    }

    sort(edg2.begin(), edg2.end());
    ll ans = 0;
    for (auto e : edg2) {
        if (find(e.from) != find(e.to)) {
            unionset(e.from, e.to, 0);
            ans += e.cost;
        }
    }
    set<int> ss;
    for (i = 1; i <= N; ++i) {
        ss.insert(find(i));
    }

    if ((int) ss.size() > 1) {
        printf("impossible\n");
    } else {
        printf("%lld\n", ans);
    }
    return 0;
}