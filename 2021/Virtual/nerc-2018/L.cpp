#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
pair<ll, int> p[MAX_SIZE];
int visited[MAX_SIZE], vis[MAX_SIZE];

int main() {
    int N, K, i;
    scanf("%d%d", &N, &K);
    for (i = 0 ; i < N; ++i) {
        scanf("%d", &p[i].second);
    }

    for (i = 0 ; i < N; ++i) {
        scanf("%lld", &p[i].first);
    }

    sort(p, p + N);

    ll ans = 0;
    for (i = N - 1; i >= 0 && K > 0; --i) {
        if (!visited[p[i].second]) {
            visited[p[i].second] = 1;
            vis[i] = 1;
            --K;
        }
    }

    for (i = 0 ; i < N && K > 0; ++i) {
        if (!vis[i]) {
            ans += p[i].first;
            --K;
        }
    }

    printf("%lld\n", ans);
    return 0;
}