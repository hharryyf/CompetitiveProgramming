#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE];

int main() {
    int i, L, N, cnt = 0;
    scanf("%d%d", &L, &N);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 2; i <= N; ++i) {
        if (a[i-1] > a[i]) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}