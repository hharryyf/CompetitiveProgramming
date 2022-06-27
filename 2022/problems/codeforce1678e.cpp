#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int f[MAX_SIZE], sz[MAX_SIZE], a[MAX_SIZE], b[MAX_SIZE], pb[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        f[fx] = fy;
        sz[fy] += sz[fx];
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            f[i] = i;
            sz[i] = 1;
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &b[i]);
            pb[b[i]] = i;
        }

        for (i = 1; i <= N; ++i) {
            unionset(i, pb[a[i]]);
        }

        long long ans = 0;
        for (i = 1; i <= N; ++i) {
            if (find(i) == i) {
                ans = ans + sz[i] / 2;
            }
        }


        printf("%lld\n", ans * 2 * (N - ans));
    }
    return 0;
}