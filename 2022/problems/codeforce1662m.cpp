#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;

int r[111], w[111];

int main() {
    int T, N, M, i;
    scanf("%d", &T);
    while (T-- > 0) {
        int R = 0, W = 0;
        scanf("%d%d", &N, &M);
        for (i = 1; i <= M; ++i) {
            scanf("%d%d", &r[i], &w[i]);
            R = max(R, r[i]);
            W = max(W, w[i]);
        }

        if (R + W <= N) {
            for (i = 1; i <= R; ++i) {
                printf("R");
            }

            for (i = 1; i <= N - R; ++i) {
                printf("W");
            }
            printf("\n");
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
    return 0;
}