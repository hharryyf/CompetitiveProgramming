#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll N;

int main() {
    ll i;
    scanf("%lld", &N);
    ll sq = sqrt(N), M = N;
    ll a = 1, b = 1;
    for (i = 2; i <= sq; ++i) {
        if (M % i == 0) {
            while (M > 0 && M % i == 0) {
                a *= i;
                M = M / i;
            }
            b = M;
            break;
        }
    }

    if (a == 1 || b == 1) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    ll x = 1, y = 1;
    gcd(a, b, x, y);
    // post-condition: a * x + b * y = 1
    y = y * (N - 1);
    x = x * (N - 1);
    if (x < 0) {
        ll xx = -x;
        xx = xx / b + (xx % b != 0);
        //printf("%lld\n", xx);
        x = x + xx * b;
        y = y - xx * a;
    } else if (y < 0) {
        ll xx = -y;
        xx = xx / a + (xx % a != 0);
        //printf("%lld\n", xx);
        x = x - xx * b;
        y = y + xx * a;
    }
    printf("2\n%lld %lld\n%lld %lld\n", y, a, x, b);
    return 0;
}