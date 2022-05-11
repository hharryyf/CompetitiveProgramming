#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve() {
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    int L, N, M, i, X, Y;
    scanf("%d%d%d", &L, &N, &M);
    X = L, Y = L;
    for (i = 1; i <= N; ++i) {
        ll v;
        scanf("%lld", &v);
        q.push({v, v});
    }

    vector<ll> wait, dry;
    while (X > 0) {
        auto v = q.top();
        q.pop();
        wait.push_back(v.first);
        X--;
        q.push({v.first + v.second, v.second});
    }

    while (!q.empty()) q.pop();

    for (i = 1; i <= M; ++i) {
        ll v;
        scanf("%lld", &v);
        q.push({v, v});
    }

    while (Y > 0) {
        auto v = q.top();
        q.pop();
        dry.push_back(v.first);
        Y--;
        q.push({v.first + v.second, v.second});
    }

    reverse(dry.begin(), dry.end());

    ll ans = 0;
    for (i = 0 ; i < (int) dry.size(); ++i) {
        ans = max(ans, dry[i] + wait[i]);
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}