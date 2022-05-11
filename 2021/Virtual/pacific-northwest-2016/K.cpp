#include <bits/stdc++.h>
#define MAX_SIZE 1100011
typedef long double ld;
using namespace std;



ld fac[MAX_SIZE];

ld logC(int n, int k) {
    return fac[n] - fac[n-k] - fac[k];
}

int main() {
    int i;
    for (i = 1 ; i < MAX_SIZE; ++i) {
        fac[i] = fac[i-1] + log(i);
    }

    int N, R;
    ld ans = 0;
    scanf("%d%d", &N, &R);
    for (i = 1; i <= N; ++i) {
        if ((1 << i) - 1 > (1 << N) - R) continue;
        ans = ans + exp(logC((1 << N) - R, (1 << i) - 1) - logC((1<<N) - 1, (1 << i) - 1));
    } 

    printf("%.5Lf\n", ans);
    return 0;
}