#include <bits/stdc++.h>

using namespace std;

int main() {
    int T, t;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {
        int N, i;
        printf("Case #%d: ", t);
        scanf("%d", &N);
        double ans = 0;
        for (i = 0 ; i < N + 1; ++i) {
            double v;
            scanf("%lf", &v);
            ans += v;
        }

        double tt = 0;
        for (i = 0 ; i < N; ++i) {
            double a, b;
            scanf("%lf%lf", &a, &b);
            tt = max(tt, b);
        }

        printf("%.6lf\n", 1.0 * (tt + ans));
    }
    return 0;
}