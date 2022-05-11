#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int f[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

set<pair<int, int>> edg;

struct qrs {
    char tp[2];
    int x, y;
};

qrs q[MAX_SIZE];
vector<int> ans;

int main() {
    int N, F, Q, i;
    scanf("%d%d%d", &N, &F, &Q);
    for (i = 0 ; i < MAX_SIZE; ++i) f[i] = i;
    for (i = 0 ; i < F; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edg.insert({u, v});
    }

    for (i = 0 ; i < Q; ++i) {
        scanf("%s%d%d", q[i].tp, &q[i].x, &q[i].y);
        if (q[i].tp[0] == 'E') {
            edg.erase({q[i].x, q[i].y});
        }
    }

    for (auto e : edg) {
        unionset(e.first, e.second);
    }

    for (i = Q - 1; i >= 0; --i) {
        if (q[i].tp[0] == 'E') {
            unionset(q[i].x, q[i].y);
        } else {
            ans.push_back(find(q[i].x) == find(q[i].y));
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto v : ans) {
        printf("%s\n", v ? "YES" : "NO");
    }
    return 0;
}