#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        vector<pair<ll, int>> pos;
        vector<ll> val;
        int N, K;
        scanf("%d%d", &N, &K);
        for (int i = 0 ; i < N; ++i) {
            ll v;
            scanf("%lld", &v);
            val.push_back(v);
            pos.emplace_back(-v + N - i - 1, i);
        }
        sort(pos.begin(), pos.end());
        for (int i = 0 ; i < K; ++i) {
            val[pos[i].second] = 0;
        }

        ll ans = 0, sm = 0;
        for (int i = 0 ; i < N; ++i) {
            if (val[i] != 0) {
                ans = ans + val[i] + sm;
            }
            if (val[i] == 0) sm++;
        }

        printf("%lld\n", ans);
    }
    return 0;
}