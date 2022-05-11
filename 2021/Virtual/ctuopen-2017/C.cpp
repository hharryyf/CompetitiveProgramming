#include <bits/stdc++.h>

using namespace std;

int N;
char s[2];

int main() {
    while (scanf("%d%s", &N, s) != EOF) {
        if (s[0] == 'N') {
            if (N <= 2) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        } else if (s[0] == 'K') {
            if (N == 1) {
                printf("1\n");
            } else {
                printf("4\n");
            }
        } else if (s[0] == 'B') {
            printf("%d\n", N);
        } else {
            printf("%d\n", N);
        }
    }
    return 0;
}