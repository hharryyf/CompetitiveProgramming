#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 1511

int a[MAX_SIZE][MAX_SIZE], row[MAX_SIZE][MAX_SIZE], col[MAX_SIZE][MAX_SIZE];
vector<int> tmp;
int N;


int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (i = 1; i <= N; ++i) {
        tmp.clear();
        for (j = 1; j <= N; ++j) {
            tmp.push_back(a[i][j]);
        }

        sort(tmp.begin(), tmp.end());

        for (j = 1; j <= N; ++j) {
            int idx = lower_bound(tmp.begin(), tmp.end(), a[i][j]) - tmp.begin();
            row[i][j] = idx;
        }
    }

    for (j = 1; j <= N; ++j) {
        tmp.clear();
        for (i = 1; i <= N; ++i) {
            tmp.push_back(a[i][j]);
        }

        sort(tmp.begin(), tmp.end());

        for (i = 1; i <= N; ++i) {
            int idx = lower_bound(tmp.begin(), tmp.end(), a[i][j]) - tmp.begin();
            col[i][j] = idx;
        }
    }

    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            ans = ans + row[i][j] * (N - col[i][j] - 1) + col[i][j] * (N - row[i][j] - 1);
        }
    }

    printf("%lld\n", ans / 2);
    return 0;
}