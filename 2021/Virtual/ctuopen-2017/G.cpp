#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int N, K, tol = 0, sm = 0;
int visited[MAX_SIZE];
vector<int> g[MAX_SIZE];

void inc(int x, int v) {
    if (v == 1) {
        visited[x]++;
        sm++;
        if (visited[x] == 1) tol++;
    } else {
        visited[x]--;
        sm--;
        if (visited[x] == 0) tol--;
    }
}

int main() {
    int i, j;
    while (scanf("%d%d", &N, &K) != EOF) {
        tol = sm = 0;
        for (i = 0; i < N; ++i) g[i].clear();
        for (i = 1; i <= K; ++i) visited[i] = 0;
        for (i = 0; i < N; ++i) {
            int v, u;
            scanf("%d", &v);
            while (v-- > 0) {
                scanf("%d", &u);
                g[i].push_back(u);
                visited[u]++;
            }
        }

        bool valid = true;
        for (i = 1 ; i <= K; ++i) {
            if (visited[i] == 0) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            printf("-1\n");
            continue;
        }

        for (i = 1; i <= K; ++i) visited[i] = 0;

        int ans = 100000001;
        for (i = 0, j = 0 ; i < N; ++i) {
            while (j < i + N && tol < K) {
                for (auto v : g[j % N]) {
                    inc(v, 1);
                }
                ++j;
            }

            ans = min(ans, sm);           

            for (auto v : g[i]) inc(v, -1);
        }

        printf("%d\n", ans);
    }
    return 0;
}