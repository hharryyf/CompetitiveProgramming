#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;

int a[12];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        for (i = 1; i <= 10; ++i) a[i] = -1;
        int N;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            int b, d;
            scanf("%d%d", &b, &d);
            a[d] = max(a[d], b);
        }

        int ans = 0;
        for (i = 1; i <= 10; ++i) {
            if (a[i] == -1) {
                ans = -1;
                break;
            }
            ans = ans + a[i];
        }

        if (ans == -1) {
            printf("MOREPROBLEMS\n");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}