#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void bad() {
    printf("NO\n");
    exit(0);
}

int main() {
    int N, D;
    scanf("%d%d", &N, &D);
    while (N-- > 0) {
        ll x, a, g, r;
        cin >> x >> a >> g >> r;
        x -= a;
        if (x < 0) bad();
        if (x == 0) continue;
        if (x % (g + r) > g) bad();
    }

    printf("YES\n");
    return 0;
}