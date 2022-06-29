#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, c1 = 0, c2 = 0;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &a[i]);
            if (a[i] % 2 == 1) {
                c1++;
            } else {
                c2++;
            }
        }
        printf("%d\n", min(c1, c2));
    }
    return 0;
}