#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x == 0 && y == 0) {
            printf("0\n");
        } else {
            int z = sqrt(x * x + y * y);
            if (z * z == x * x + y * y) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        }
    }
    return 0;
}