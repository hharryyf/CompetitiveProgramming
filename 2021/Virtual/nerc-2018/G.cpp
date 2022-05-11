#include <bits/stdc++.h>
#define MAX_SIZE 8
using namespace std;

int a[MAX_SIZE];

int calc(int pos, int rem) {
    int cnt = 0;
    while (rem > 0) {
        ++cnt;
        if (a[pos]) rem--;
        pos++;
        if (pos == 7) pos = 0;
    }
    return cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int ans = 0, tol = 0, N, i, rd = 0;
        scanf("%d", &N);
        for (i = 0 ; i < 7; ++i) {
            scanf("%d", &a[i]);
            tol += a[i];
        }

        rd = max(N - tol, 0) / tol;
        ans += rd * 7;
        N -= rd *  tol;
        int day = 28;
        for (i = 0 ; i < 7; ++i) {
            day = min(day, calc(i, N));
        }

        printf("%d\n", ans + day);
    }
    return 0;
}