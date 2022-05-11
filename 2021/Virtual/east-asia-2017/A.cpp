#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

ll fastpower(ll v, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p % 2 == 1) {
            ret = ret * v;
            ret %= mod;
            p--;
        } else {
            v = v * v;
            v %= mod;
            p = p / 2;
        }
    }

    return ret;
}

void solve(int N, int K) {
    if (N < K) {
        printf("0\n");
        return;
    }

    ll ret = fastpower(2, N) - 1;
    // ret -= c[N][1] + c[N][2] + ... + c[N][K-1]
    // n * (n-1) * ... * (n - k + 1) /k!
    ll high = N, low = 1;
    ret -= high;
    for (int i = 2; i < K; ++i) {
        high = high * (N - i + 1);
        low = low * fastpower(i, mod - 2);
        high %= mod;
        low %= mod;
        ret -= low * high;
        ret %= mod;
    }

    ret = (ret % mod + mod) % mod;
    printf("%lld\n", ret);
}

int main() {
    int T, t;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {
        int N, K;
        printf("Case #%d: ", t);
        scanf("%d%d", &N, &K);
        solve(N, K);
    }
    return 0;
}