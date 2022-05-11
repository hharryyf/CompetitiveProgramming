#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;
int a[MAX_SIZE], M, N;

int main() {
    int i, l = 1, ans = 1;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        if (i == 1 || a[i] - a[i-1] <= M) {
            ans = max(ans, i - l + 1);
        } else {
            l = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}