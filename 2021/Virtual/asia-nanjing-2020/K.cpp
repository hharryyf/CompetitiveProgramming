#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int a[MAX_SIZE];

int main() {
    int N, K, i;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        a[i] = i;
    }

    if (K == 0) {
        printf("-1\n");
        return 0;
    }

    if (K % 2 == 1) {
        K -= 1;
        for (i = 2; i + 1 <= N && K > 0; i += 2, K -= 2) {

            swap(a[i], a[i+1]);
        }
    } else {
        for (i = 1; i + 1 <= N && K > 0; i += 2, K -= 2) {
            swap(a[i], a[i+1]);
        }
    }

    for (i = 1; i <= N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}