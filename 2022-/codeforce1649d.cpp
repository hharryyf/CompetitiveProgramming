#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;
//#define L
#ifdef L
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

int cnt[MAX_SIZE], visited[MAX_SIZE];
int N, C;
void solve() {
    int i, j;
    for (i = 1; i <= C; ++i) {
        for (j = 1; j * i <= C; ++j) {
            int low = i * j, high = min(j * (i + 1) - 1, C);
            if (cnt[high] - cnt[low - 1] != 0 && visited[i] != 1 && visited[j] == 1) {
                debug("mod=%d, num=%d, low=%d high=%d invalid\n", i, j, low, high);
                printf("No\n");
                return;
            }
        }
    }

    printf("Yes\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &C);
        int i;
        for (i = 1; i <= C; ++i) visited[i] = cnt[i] = 0;
        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            visited[v] = 1;
            cnt[v] += 1;
        } 

        for (i = 1; i <= C; ++i) cnt[i] += cnt[i-1];

        solve();
    }
    return 0;
}