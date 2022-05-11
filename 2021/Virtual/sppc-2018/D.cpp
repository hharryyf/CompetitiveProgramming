#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

/*
    l[1] + l[2] + ... + l[n] + r[1] = h[1]
    l[2] + ...        + l[n] + r[1] + r[2] = h[2]
    l[n] + r[1] + r[2] + ... + r[n] = h[n]
    l[i] >= 0 and r[i] >= 0
    Then, we know that r[2] - l[1] = h[2] - h[1],
    r[3] - l[2] = h[3] - h[2],
    ...
    r[n] - l[n-1] = h[n] - h[n-1]
    if h[i] > h[i-1] --> r[i] - l[i-1] > 0, and we know that r[i] >= h[i] - h[i-1]
    if h[i] < h[i-1] --> r[i] - l[i-1] < 0, and we know that l[i-1] >= h[i-1] - h[i]
    and check the sum of all critical points 
*/

ll h[MAX_SIZE];
ll L, R;

int main() {
    int N, i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%lld", &h[i]);
    L = h[1], R = h[N];
    for (i = 2; i <= N; ++i) {
        if (h[i] > h[i-1]) R -= h[i] - h[i-1];
        if (h[i] < h[i-1]) L += h[i] - h[i-1];
        if (L < 0 || R < 0) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}