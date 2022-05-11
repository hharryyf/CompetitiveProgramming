#include <bits/stdc++.h>

using namespace std;

char ans[111][111];

int M, N;

void init() {
    int i, j;
    for (i = 0 ; i <= M + 1; ++i) {
        for (j = 0 ; j <= M + 1; ++j) {
            ans[i][j] = '.';
        }
    }

    for (i = 0 ; i <= M + 1; ++i) {
        for (j = 0 ; j <= M + 1; ++j) {
            if (i == 0 || j == 0 || i == M + 1 || j == M + 1) ans[i][j] = '*';
        }
    }
}

bool inside(int x, int y) {
    return x >= 1 && x <= M && y >= 1 && y <= M;
}

int main() {
    int i, j, t;
    while (scanf("%d%d", &M, &N) != EOF) {
        init();

        for (t = 0 ; t < N; ++t) {
            int h, x, y;
            scanf("%d%d%d", &h, &x, &y);
            x++, y++;
            if (h == 0) {
                if (inside(y, x)) ans[y][x] = 111;
                if (inside(y, x - 1)) ans[y][x-1] = 95;
                if (inside(y, x + 1)) ans[y][x+1] = 95;
            } else {
                // plot the root
                if (inside(y, x)) ans[y][x] = 124;
                if (inside(y, x - 1)) ans[y][x-1] = 95;
                if (inside(y, x + 1)) ans[y][x+1] = 95;
                // print the top
                if (inside(y + h + 1, x)) ans[y + h + 1][x] = 94;
                // print the center
                int low = 1, high = M;
                low = max(low, y + 1);
                high = min(high, y + h);
                if (inside(1, x)) {
                    for (i = low; i <= high; ++i) ans[i][x] = 124;
                }
                // print the left branch
                if (inside(1, x - 1)) {
                    for (i = low; i <= high; ++i) ans[i][x-1] = 47;
                }
                // print the right branch
                if (inside(1, x + 1)) {
                    for (i = low; i <= high; ++i) ans[i][x+1] = 92;
                }
            }
        }

        for (i = M + 1 ; i >= 0; --i) {
            for (j = 0 ; j <= M + 1; ++j) {
                printf("%c", ans[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}