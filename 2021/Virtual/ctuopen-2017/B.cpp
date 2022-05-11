#include <bits/stdc++.h>
typedef long double ld;
#define MAX_SIZE 100011
using namespace std;

ld a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE], F;
int N;

bool check_low(ld T) {
    int i;
    for (i = 1; i <= N; ++i) c[i] = a[i];
    for (i = 1; i <= N; ++i) {
        c[i] -= T * F;
        if (c[i] > 0) continue;
        c[i + 1] -= -c[i];
        c[i] = 0;
    }

    return c[N] <= 0;
}

ld solve_low() {
    int i;
    ld low = 0, high = 0;
    for (i = 1; i <= N; ++i) {
        high = max(high, a[i] / F);
        b[i] = a[i];
    }

    ld ret = high;
    
    for (i = 0 ; i < 70; ++i) {
        ld mid = 0.5 * (low + high);
        if (check_low(mid)) {
            ret = mid;
            high = mid;
        } else {
            low = mid;
        }
    }
    return ret;
}

bool check_all(ld T) {
    int i;
    for (i = 1; i <= N; ++i) c[i] = a[i];
    for (i = 1; i <= N; ++i) {
        c[i] -= T * F;
        if (c[i] > 0) return false;
        c[i + 1] -= -c[i];
    }

    return true;
}

ld solve_all() {
    int i;
    ld low = 0, high = 0;
    for (i = 1; i <= N; ++i) {
        a[i] = b[i];
        high = max(high, a[i] / F);
    }

    ld ret = high;

    for (i = 0 ; i < 70; ++i) {
        ld mid = 0.5 * (low + high);
        if (check_all(mid)) {
            ret = mid;
            high = mid;
        } else {
            low = mid;
        }
    }
    return ret;
}

int main() {
    int i;
    while (scanf("%d%Lf", &N, &F) != EOF) {
        for (i = 1; i <= N; ++i) {
            scanf("%Lf", &a[i]);
        }

        printf("%.9Lf ", solve_low());
        printf("%.9Lf\n", solve_all());
    }
    return 0;
}