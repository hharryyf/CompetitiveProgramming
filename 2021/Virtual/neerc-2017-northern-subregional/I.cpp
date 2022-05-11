#include <bits/stdc++.h>

using namespace std;
int N;

#define FILEIO


void openfile(string filename="intel") {
    #ifdef FILEIO
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
    #endif
}
typedef long long ll;
ll x[1011], y[1011];

int main() {
    openfile();
    int i;
    ll ans = 0, tx = -1e9, lx = 1e9, ty = -1e9, ly = 1e9;
    scanf("%d", &N);    
    for (i = 1; i <= N; ++i) {
        scanf("%lld%lld", &x[i], &y[i]);
        tx = max(tx, x[i]);
        lx = min(lx, x[i]);
        ly = min(ly, y[i]);
        ty = max(ty, y[i]);
    }
    for (i = 2; i <= N; ++i) {
        if (y[i] == y[i-1]) {
            ans += abs(x[i] - x[i-1]);
        } else {
            ans += abs(y[i] - y[i-1]);
        }
    }

    if (y[1] == y[N]) {
        ans += abs(x[1] - x[N]);
    } else {
        ans += abs(y[1] - y[N]);
    }

    ans -= 2ll * (tx - lx) + 2ll * (ty - ly);
    printf("%lld\n", ans);
    return 0;
}