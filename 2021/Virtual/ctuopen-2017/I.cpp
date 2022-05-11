#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100011
using namespace std;

int N;
int x[MAX_SIZE], y[MAX_SIZE];

int main() {
    while (scanf("%d", &N) != EOF) {
        int i;
        ll ans = 0;
        for (i = 1; i <= N; ++i) scanf("%d%d", &x[i], &y[i]);
        map<int, int> cnt;
        for (i = 1; i <= N; ++i) {
            cnt[x[i] + y[i]]++;
        }

        for (auto iter : cnt) {
            ans = ans + 1ll * iter.second * (iter.second - 1);
        }

        cnt.clear();
        for (i = 1; i <= N; ++i) {
            cnt[x[i] - y[i]]++;
        }

        for (auto iter : cnt) {
            ans = ans + 1ll * iter.second * (iter.second - 1);
        }

        printf("%.9lf\n", 1.0 * ans / (1.0 * N * N));
    }
    return 0;
}