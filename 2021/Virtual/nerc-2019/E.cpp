#include <bits/stdc++.h>

using namespace std;

int a[111][111];
vector<int> ans[111];
int N, M;

int judge(int pos) {
    int ret1 = 0, ret2 = 0, i;
    vector<pair<int, int>> p;
    for (i = 1; i <= M; ++i) {
        ret1 += a[i][pos], ret2 += a[i][N];
        p.emplace_back(a[i][pos] - a[i][N], i);
    }

    int ret = 0, df = ret2 - ret1;
    sort(p.begin(), p.end());
    for (i = 0; i < (int) p.size(); ++i) {
        if (df <= 0) break;
        ret++;
        ans[pos].push_back(p[i].second);
        df += p[i].first;
    }

    return ret;
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    int ans1 = M + 1, idx = -1;
    for (i = 1; i < N; ++i) {
        int val = judge(i);
        if (ans1 > val) {
            ans1 = val;
            idx = i;
        }
    }

    printf("%d\n", ans1);
    //printf("%d\n", idx);
    for (auto v : ans[idx]) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}