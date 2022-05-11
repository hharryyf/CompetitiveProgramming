#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE], T, N;

int main() {
    int i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        int cnt = 0;
        for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
        while (true) {
            bool ok = true;
            for (i = N; i >= 2; --i) {
                if (a[i] != a[i-1]) {
                    ok = false;
                    cnt++;
                    int num = a[i];
                    // fill [i, N] [i-(N-i+1), i-1]
                    for (int j = max(1, i - (N - i + 1)); j <= i - 1; ++j) {
                        a[j] = num;
                    }
                    break;
                }
            }

            if (ok) {
                printf("%d\n", cnt);
                break;
            }
        }
    }   
    return 0;
}