#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll hc, dc, hm, dm;
        int K;
        ll w, a;
        scanf("%lld%lld%lld%lld", &hc, &dc, &hm, &dm);
        scanf("%d%lld%lld", &K, &w, &a);
        bool ok = false;
        for (int i = 0 ; i <= K; ++i) {
            // i for attach, K - i for defense
            ll d = w * (K - i) + dc, h = a * i + hc;
            ll r1 = h / dm - (h % dm == 0);
            ll r2 = hm / d - (hm % d == 0);
            // cout << h << " " << d << " " << hm << " " << dm << " " << r1 << " " << r2 << endl;
            if (r1 >= r2) {
                ok = true;
                break;
            }
        }

        if (ok) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}