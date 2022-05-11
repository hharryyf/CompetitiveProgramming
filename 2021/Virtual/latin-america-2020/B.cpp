#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE], inc[MAX_SIZE], dec2[MAX_SIZE], N;

bool check(int L, int R) {
    if (R - L + 1 < 3) return false;
    int r = min(R - 1, inc[L]);
    if (r == L || dec2[r] < R) return false;
    return true; 
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    inc[N] = dec2[N] = N;

    for (i = N - 1; i >= 1; --i) {
        inc[i] = dec2[i] = i;
        if (a[i] == -1 || a[i+1] == -1 || a[i] <= a[i+1]) inc[i] = inc[i+1];
        if (a[i] == -1 || a[i+1] == -1 || a[i] >= a[i+1]) dec2[i] = dec2[i+1];
    }

    for (i = 3; i <= N; ++i) {
        bool ok = true;
        for (int j = 1; j <= N; j += i) {
            int L = j, R = min(j + i - 1, N);
            if (!check(L, R)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            printf("Y\n");
            return 0;
        }
    }

    printf("N\n");
    return 0;
}