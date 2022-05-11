#include <bits/stdc++.h>

using namespace std;

int c[4];

int main() {
    int N;
    scanf("%d", &N);
    int i;
    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        c[v]++;
    }

    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        c[v]--;
    }

    if (c[1] == 0 && c[2] == 0 && c[3] == 0) {
        printf("marvelous\n");
    } else {
        printf("error\n");
    }
    return 0;
}