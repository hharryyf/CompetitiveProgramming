#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;


int cnt[MAX_SIZE], a[MAX_SIZE], b[MAX_SIZE];
int N, K;

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &K);
        for (i = 1; i <= N; ++i) cnt[i] = 0;
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            cnt[a[i]]++;
        }
        
        int sm = -N, ans = N + 1;
        int x = 1, y = 0;
        for (i = 1, j = 0; i <= N; ++i) {
            while (j < N && sm < K) {
                sm += 2 * cnt[++j];
            }

            if (sm >= K && ans > j - i + 1) {
                x = i, y = j;
                ans = j - i + 1;
            }
            sm -= 2 * cnt[i];
        }

        printf("%d %d\n", x, y);
        for (i = 1; i <= N; ++i) {
            if (a[i] >= x && a[i] <= y) {
                b[i] = 1;
            } else {
                b[i] = -1;
            }
        }

        sm = 0;
        int tol = 0, pre = 0;
        if (K == 1) {
            printf("%d %d\n", 1, N);
        } else {
            for (i = 1; i <= N; ++i) {
                sm += b[i];
                if (sm > 0) {
                    tol++;
                    sm = 0;
                    printf("%d %d\n", pre + 1, i);
                    pre = i;
                }

                if (tol == K - 1) {
                    printf("%d %d\n", i + 1, N);
                    break;
                }
            }
        }
    }
    return 0;
}