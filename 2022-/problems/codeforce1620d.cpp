#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 111
int a[MAX_SIZE], N;

bool ok(int v, int c1, int c2, int c3) {
    debug("check v=%d, c1=%d, c2=%d, c3=%d\n", v, c1, c2, c3);
    for (int i = 0; i <= c1; ++i) {
        for (int j = 0; j <= c2; ++j) {
            int d = v - i - j * 2;
            if (d >= 0 && d % 3 == 0 && d <= c3 * 3) {
                debug("ok, (%d,%d,%d)\n", i, j, d / 3);
                return true;
            }
        }
    }

    debug("fail\n");
    return false;
}

bool check(int c1, int c2, int c3) {
    int i;
    for (i = 1; i <= N; ++i) {
        if (!ok(a[i], c1, c2, c3)) return false;
    }    

    return true;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        int mx = a[1], tol = 1e9;
        for (i = 2; i <= N; ++i) mx = max(a[i], mx);
        for (int c1 = 0; c1 <= 3; ++c1) {
            for (int c2 = 0; c2 <= 3; ++c2) {
                int c3 = max(0, (mx + 2 - 2 * c2 - c1) / 3);
                if (check(c1, c2, c3)) {
                    tol = min(tol, c1 + c2 + c3);
                }
            }
        }

        printf("%d\n", tol);
    }
    return 0;
}