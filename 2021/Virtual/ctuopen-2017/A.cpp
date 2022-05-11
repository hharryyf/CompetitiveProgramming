#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int N, a[MAX_SIZE];

int main() {
    int i;
    while (scanf("%d", &N) != EOF) {
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        if (N <= 2) {
            printf("1\n");
        } else {
            int ans = N - 1;
            for (i = N - 2; i >= 1; --i) {
                if (a[i+2] - a[i+1] == a[i+1] - a[i]) {
                    ans = i;
                } else {
                    break;
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}