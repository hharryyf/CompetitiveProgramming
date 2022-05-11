#include <bits/stdc++.h>

using namespace std;

int a[111], b[111];
int T;
int N;

int main() {
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        for (i = 1; i <= N; ++i) scanf("%d", &b[i]);
        for (i = 1; i <= N; ++i) {
            if (a[i] > b[i]) swap(a[i], b[i]);
        }

        int mx1 = -1, mx2 = -1;
        for (i = 1; i <= N; ++i) {
            mx1 = max(mx1, a[i]);
            mx2 = max(mx2, b[i]);
        }

        printf("%d\n", mx1 * mx2);
    }
    return 0;
}