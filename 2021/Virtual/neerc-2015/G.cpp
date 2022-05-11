#include <bits/stdc++.h>
#define SUBMIT
#define MAX_SIZE 1011
using namespace std;

int visited[MAX_SIZE];

pair<pair<int, int>, pair<int, int>> gen(int a, int b, int c, int x0) {
    vector<pair<int, int>> d;
    int ord = 0;
    memset(visited, 0, sizeof(visited));
    while (!visited[x0]) {
        visited[x0] = 1;
        d.emplace_back(x0, ord++);
        x0 = (a * x0 + b) % c;
    }

    sort(d.begin(), d.end());
    if ((int) d.size() == 1) {
        return {d.back(), d.back()};
    }

    return {d.back(), d[(int) d.size() - 2]};
}

int ans[10011];

int main() {
    #ifdef SUBMIT
    freopen("generators.in", "r", stdin);
    freopen("generators.out", "w", stdout);
    #endif
    int i, N, K;
    scanf("%d%d", &N, &K);
    vector<pair<pair<int, pair<pair<int, int>, pair<int, int>>>, int>> ret;
    for (i = 1; i <= N; ++i) {
        int a, b, c, x0;
        scanf("%d%d%d%d", &x0, &a, &b, &c);
        auto p = gen(a, b, c, x0);
        ret.push_back(make_pair(make_pair(p.first.first - p.second.first, p), i));
    }

    sort(ret.begin(), ret.end());
    int tol = 0;
    for (i = 0 ; i < (int) ret.size(); ++i) {
        tol += ret[i].first.second.first.first;
    }

    if (tol % K != 0) {
        printf("%d\n", tol);
        for (i = 0 ; i < (int) ret.size(); ++i) {
            ans[ret[i].second] = ret[i].first.second.first.second;
        }   

        for (i = 0 ; i < (int) ret.size(); ++i) {
            printf("%d ", ans[i+1]);
        }
        printf("\n");
    } else {
        bool flag = false;
        for (i = 0 ; i < (int) ret.size(); ++i) {
            ans[ret[i].second] = ret[i].first.second.first.second;
            if (!flag && ret[i].first.first % K != 0) {
                tol -= ret[i].first.first;
                ans[ret[i].second] = ret[i].first.second.second.second;
                flag = true;
            }
        }   

        if (!flag) {
            printf("-1\n");
            return 0;
        }

        printf("%d\n", tol);
        for (i = 0 ; i < (int) ret.size(); ++i) {
            printf("%d ", ans[i+1]);
        }

        printf("\n");
    }
    return 0;
}