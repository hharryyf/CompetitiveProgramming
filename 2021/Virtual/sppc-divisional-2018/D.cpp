#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

ll den, num = 0;
int N;

int main() {
    int i;
    scanf("%d", &N);
    den = 1ll * N * (N + 1) / 2;
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        num += 1ll * v * i * (N - i + 1);
    }

    ll g = __gcd(num, den);
    num /= g;
    den /= g;
    printf("%lld/%lld\n", num, den);
    return 0;
}