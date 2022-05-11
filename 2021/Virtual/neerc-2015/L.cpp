#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
#define SUBMIT
ll W, a[MAX_SIZE], pre[MAX_SIZE];
int N, L[MAX_SIZE], R[MAX_SIZE];

void openfile() {
    freopen("landscape.in", "r", stdin);
    freopen("landscape.out", "w", stdout);
}

bool check(ll h) {
    int i;
    for (i = 0; i < MAX_SIZE; ++i) {
        L[i] = 0, R[i] = MAX_SIZE;
    }

    for (i = 1; i <= N; ++i) {
        ll l = 1ll * i + (h - a[i]);
        ll r = 1ll * i - h + a[i];
        if (l <= N) L[(int) l] = max(L[(int) l], i);
        if (r >= 1) R[(int) r] = min(R[(int) r], i);
    }

    for (i = 1; i <= N; ++i) {
        L[i] = max(L[i-1], L[i]);
    }

    for (i = N; i >= 1; --i) {
        R[i] = min(R[i+1], R[i]);
    }

    for (i = 1; i <= N; ++i) {
        if (L[i] == 0 || R[i] == MAX_SIZE) continue;
        ll curr = 1ll * (h * 2 - i + L[i] + 1) * (i - L[i]) / 2 + 1ll * (h * 2 - R[i] + i + 1) * (R[i] - i) / 2;
        curr -= h;
        curr -= pre[R[i] - 1] - pre[L[i]];
        if (curr <= W) return true;
    }
    return false;
}

int main() {
    #ifdef SUBMIT
    openfile();
    #endif
    ll maxh = 0;
    int i;
    scanf("%d%lld", &N, &W);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &a[i]);
        pre[i] = pre[i-1] + a[i];
        maxh = max(maxh, a[i]);
    }

    ll low = maxh, high = 2e9, ans = maxh;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%lld\n", ans);
    return 0;
}