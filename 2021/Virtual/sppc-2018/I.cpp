#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll ans;
int cnt[13], N, M, cnt2[14], cnt3[14];
ll fac[13];

void dfs(int pos, int sm) {
    if (pos > N) return;
    if (pos == N && sm != 0) return;
    if (pos == N) {
        ll den = 1, num = 1;
        for (int i = 0 ; i < N; ++i) {
            den *= fac[cnt[i]];
        }

        memset(cnt2, 0, sizeof(cnt2));
        memset(cnt3, 0, sizeof(cnt3));
        for (int i = 0 ; i < N; ++i) {
            cnt2[cnt[i] % M]++;
            cnt3[i % M] += cnt[i];
        }

        for (int i = 0 ; i < N; ++i) {
            if (cnt2[i] != cnt3[i]) return;
            num *= fac[cnt2[i]];
        }
        ans += num / den;
        return;
    }
    int i;
    for (i = 0; i <= sm; ++i) {
        cnt[pos] = i;
        dfs(pos + 1, sm - i); 
    }
}

int main() {
    scanf("%d%d", &N, &M);
    fac[0] = 1;
    for (int i = 1; i <= 12; ++i) fac[i] = fac[i-1] * i;
    dfs(0, N);
    printf("%lld\n", ans);
    return 0;   
}