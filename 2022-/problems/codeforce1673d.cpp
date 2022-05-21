#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
typedef long long ll;
const ll mod = 1e9 + 7;

ll b[3], c[3];

ll add(ll x, ll y) {
    ll ret = (x + y) % mod;
    if (ret < 0) ret += mod;
    return ret;
}

ll solve(ll d) {
    debug("check d=%lld\n", d);
    ll high = c[1] + c[2];
    ll ret = 1;
    if (high > b[2]) return -1;
    ret = ret * c[1] / d;
    ll low = c[0] - c[1];
    if (low < b[0]) return -1; 
    ret = ret * c[1] / d;
    ret %= mod;
    debug("d=%lld, ans=%lld\n", d, ret);
    return ret;
}

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%lld%lld%lld", &b[0], &b[1], &b[2]);
        scanf("%lld%lld%lld", &c[0], &c[1], &c[2]);
        b[2] = b[0] + (b[2] - 1) * b[1];
        c[2] = c[0] + (c[2] - 1) * c[1];

        if (c[0] < b[0] || c[2] > b[2]) {
            printf("0\n");
            continue;
        }

        if ((c[0] - b[0]) % b[1] != 0 || (b[2] - c[2]) % b[1] != 0) {
            printf("0\n");
            continue;
        }

        if (c[1] % b[1] != 0) {
            printf("0\n");
            continue;
        }

        ll ans = 0;
        for (int i = 1; i <= sqrt(c[1]); ++i) {
            if (c[1] % i != 0) continue;
            if (c[1] == i * i) {
                if (b[1] * i / gcd(i, b[1]) != c[1]) continue;
                ll v = solve(i);
                if (v == -1) {
                    ans = -1;
                    break;
                }
                ans = add(ans, v);
            } else {
                if (b[1] * i / gcd(i, b[1]) == c[1]) {
                    ll v = solve(i);
                    if (v == -1) {
                        ans = -1;
                        break;
                    }
                    ans = add(ans, v);
                }
                if (b[1] * (c[1] / i) / gcd((c[1] / i), b[1]) != c[1]) continue;
                ll v = solve(c[1] / i);
                if (v == -1) {
                    ans = -1;
                    break;
                }
                ans = add(ans, v);
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}