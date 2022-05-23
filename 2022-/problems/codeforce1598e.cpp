#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
typedef long long ll;
using namespace std;
#define MAX_SIZE 1011
int N, M, Q;

int a[MAX_SIZE][MAX_SIZE];

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    ll ans = 0;
    ans = ans + N * M;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            a[i][j] = 1;
        }
    }  
    // start from the first row and go to the right
    for (int i = 1; i <= M; ++i) {
        int x = 1, y = i, len = 0;
        int dx = 0, dy = 1;
        while (x <= N && y <= M) {
            len++;
            x = x + dx;
            y = y + dy;
            dx ^= 1;
            dy ^= 1;
        }
        ans = ans + len * (len - 1) / 2;
    }

    // start from the first col and go to the down
    for (int i = 1; i <= N; ++i) {
        int x = i, y = 1, len = 0;
        int dx = 1, dy = 0;
        while (x <= N && y <= M) {
            len++;
            x = x + dx;
            y = y + dy;
            dx ^= 1;
            dy ^= 1;
        }
        ans = ans + len * (len - 1) / 2;
    }

    debug("without block: %lld\n", ans);
    while (Q-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        // left->up->left->up, down->right->down->right combination
        int l = 1, r = 1;
        int tx = x, ty = y, dx = 1, dy = 0;
        while (tx <= N && ty <= M) {
            tx += dx;
            ty += dy;
            dx ^= 1;
            dy ^= 1;
            if (tx > N || ty > M) break;
            if (!a[tx][ty]) break;
            r++;
        }

        tx = x, ty = y;
        dx = 0, dy = 1;
        while (tx > 0 && ty > 0) {
            tx -= dx;
            ty -= dy;
            dx ^= 1;
            dy ^= 1;
            if (tx == 0 || ty == 0) break;
            if (!a[tx][ty]) break;
            l++;
        }

        if (!a[x][y]) {
            ans = ans + l * r;
        } else {
            ans = ans - l * r;
        }
        // up->left->up->left, right->down->right->down combination
        l = 1, r = 1;
        tx = x, ty = y, dx = 0, dy = 1;
        while (tx <= N && ty <= M) {
            tx += dx;
            ty += dy;
            dx ^= 1;
            dy ^= 1;
            if (tx > N || ty > M) break;
            if (!a[tx][ty]) break;
            r++;
        }

        tx = x, ty = y;
        dx = 1, dy = 0;
        while (tx > 0 && ty > 0) {
            tx -= dx;
            ty -= dy;
            dx ^= 1;
            dy ^= 1;
            if (tx == 0 || ty == 0) break;
            if (!a[tx][ty]) break;
            l++;
        }

        if (!a[x][y]) {
            ans = ans + l * r;
        } else {
            ans = ans - l * r;
        }

        if (a[x][y]) {
            ans++;
        } else {
            ans--;
        }

        printf("%lld\n", ans);
        a[x][y] ^= 1;
    }
    return 0;
}