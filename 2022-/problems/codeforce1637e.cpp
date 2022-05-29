#include <bits/stdc++.h>

#define MAX_SIZE 300011
typedef long long ll;
using namespace std;

//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

ll ans = 0;
vector<int> f[MAX_SIZE];


ll encode(ll u, ll v) {
    return ((u << 30ll) | v);
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        vector<ll> ban;
        map<int, int> occ;
        ans = 0;
        int u, v, N, M;
        scanf("%d%d", &N, &M);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &v);
            occ[v] += 1;
            f[i].clear();
        }

        for (i = 1; i <= M; ++i) {
            scanf("%d%d", &u, &v);
            ban.push_back(encode(u, v));
            ban.push_back(encode(v, u));
        }

        for (auto iter : occ) {
            f[iter.second].push_back(iter.first);
        }

        for (i = 1; i <= N; ++i) sort(f[i].begin(), f[i].end(), greater<int>());

        
        sort(ban.begin(), ban.end());

        for (i = 1 ; i <= N; ++i) {
            for (auto x : f[i]) {
                for (int j = 1; j <= i; ++j) {
                    for (auto y : f[j]) {
                        if (x != y && !binary_search(ban.begin(), ban.end(), encode(x, y))) {
                            ans = max(ans, 1ll * (i + j) * (x + y));
                            break;
                        }
                    }
                }
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}