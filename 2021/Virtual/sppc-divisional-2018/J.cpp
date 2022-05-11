#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int N;
int dp[MAX_SIZE];
const int inf = 1000000007;
vector<int> coin;

int main() {
    int i, C;
    for (i = 1 ; i < MAX_SIZE; ++i) dp[i] = inf;
    dp[0] = 0;
    scanf("%d%d", &N, &C);
    N *= 2520;
    for (i = 0 ; i < C; ++i) {
        int p, q;
        scanf("%d%d", &p, &q);
        p *= 2520;
        p /= q;
        coin.push_back(p);
    }

    for (i = 0 ; i <= N; ++i) {
        for (auto v : coin) {
            dp[i + v] = min(dp[i + v], dp[i] + 1);
        }
    }

    if (dp[N] >= inf) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[N]);
    }
    return 0;
}