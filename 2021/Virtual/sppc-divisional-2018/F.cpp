#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int N;
ll M;

int main() {
    int i;
    ll ret = 0;
    scanf("%d%lld", &N, &M);
    for (i = 0 ; i < N; ++i) {
        ll v;
        scanf("%lld", &v);
        ret += v;
    }

    ll ans = ret / M;
    if (ret % M != 0) ans++;
    printf("%lld\n", ans);
    return 0;
}