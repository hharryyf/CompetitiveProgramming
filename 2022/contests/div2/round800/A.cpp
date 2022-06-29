#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int a, b, i;
        scanf("%d%d", &a, &b);
        for (i = 0 ; i < min(a, b); ++i) {
            printf("01");
        }

        for (i = min(a, b); i < max(a, b); ++i) {
            if (max(a, b) == a) {
                printf("0");
            } else {
                printf("1");
            }
        }

        printf("\n");
    }
    return 0;
}