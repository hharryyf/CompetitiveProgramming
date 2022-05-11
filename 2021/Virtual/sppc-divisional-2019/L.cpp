#include <bits/stdc++.h>

using namespace std;

int row[111], col[111];
int a[111][111];

int main() {
    int sm = 0, tol = 0, N, i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &row[i]);
        sm += row[i];
        tol += row[i];
    }

    for (i = 1; i <= N; ++i) {
        scanf("%d", &col[i]);
        sm -= col[i];
    }

    if (sm != 0) {
        printf("-1\n");
        return 0;
    }

    while (tol != 0) {
        int id1 = -1, id2 = -1, r = 1000000, c = 1000000;
        for (i = 1; i <= N; ++i) {
            if (row[i] != 0 && row[i] < r) {
                r = row[i];
                id1 = i;
            }

            if (col[i] != 0 && col[i] < c) {
                c = col[i];
                id2 = i;
            }
        }

        int v = min(row[id1], col[id2]);
        a[id1][id2] = v;
        row[id1] -= v;
        col[id2] -= v;
        tol -= v;
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}