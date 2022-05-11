#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int ans[MAX_SIZE], curr[MAX_SIZE];
int N;

int getbit() {
    return (1ll * rand() * rand() + 1ll * rand() * 19260817) & 1;
}

int query(int a[]) {
    int i;
    for (i = 1; i <= N; ++i) {
        printf("%d", a[i]);
    }
    printf("\n");
    fflush(stdout);
    scanf("%d", &i);
    return i;
}

int main() {
    int i, j;
    srand(19260421);
    scanf("%d", &N);
    for (i = 1; i <= 499; ++i) {
        for (j = 1; j <= N; ++j) curr[j] = getbit();
        int val = query(curr);
        if (val == N / 2) break;
        if (val == N) {
            return 0;
        }
    }

    ans[1] = curr[1];
    curr[1] ^= 1;
    for (i = 2; i <= N; ++i) {
        curr[i] ^= 1;
        int val = query(curr);
        if (val == N / 2) {
            ans[i] = curr[i];
        } else {   
            ans[i] = curr[i] ^ 1;
        }
        curr[i] ^= 1;
    }

    if (query(ans) == N) {
        return 0;
    }

    for (i = 1; i <= N; ++i) ans[i] ^= 1;
    query(ans);
    return 0;
}