#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
ll a[MAX_SIZE];

void solve(int N) {
    int i;
    for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
    
}

int main() {
    int T, t;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {
        int N, K;
        printf("Case #%d: ", t);
        scanf("%d%d", &N);
        solve(N);
    }
    return 0;
}