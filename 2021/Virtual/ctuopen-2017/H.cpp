#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int f[MAX_SIZE], N, sz[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return;
    f[a] = b;
    sz[b] += sz[a];
}

int main() {
    int i, v;
    while (scanf("%d", &N) != EOF) {
        int ans = 0;
        for (i = 1; i <= N; ++i) {
            f[i] = i, sz[i] = 1;
        }

        for (i = 1; i <= N; ++i) {
            scanf("%d", &v);
            unionset(i, v);
        }

        for (i = 1; i <= N; ++i) {
            if (find(i) == i) ans += sz[i] - 1;
        }

        printf("%d\n", ans);
    }
    return 0;
}