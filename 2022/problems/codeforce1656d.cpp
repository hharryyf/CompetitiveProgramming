#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll N;
        scanf("%lld", &N);       
        if (N % 2 == 1) {
            printf("2\n");
            continue;
        } 

        if (N == 6) {
            printf("3\n");
            continue;
        }

        if (N == 2) {
            printf("-1\n");
            continue;
        }

        if (N % 4 == 2) {
            printf("4\n");
            continue;
        }

        ll v = 1, NN = N;
        while (N % 2 == 0) {
            N = N / 2;
            v = v * 2;
        }

        if (N == 1) {
            printf("-1\n");
            continue;
        }

        if (N < 2e9 && N * (N + 1) / 2 <= NN) {
            printf("%lld\n", N);
        } else {
            printf("%lld\n", (NN * 2) / N);
        }
    }
    return 0;
}