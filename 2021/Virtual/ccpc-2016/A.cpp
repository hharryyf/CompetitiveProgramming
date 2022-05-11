#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE];
int N;

int main() {
    int T, i;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        scanf("%d", &N);
        int tol = 0, j = 0;
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        sort(a + 1, a + 1 + N);
        for (i = N; i >= 1; --i, j = (j + 1) % 3) {
            if (j % 3 != 2) tol += a[i]; 
        }

        printf("%d\n", tol);
    }
    return 0;
}