#include <bits/stdc++.h>
#define MAX_SIZE 254
using namespace std;
typedef long long ll;
ll dp[MAX_SIZE][1347];
vector<int> fac[MAX_SIZE];
vector<int> g[MAX_SIZE];
int a[MAX_SIZE], N;

void dfs(int v, int pre) {
    int i, j;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }    

    for (i = 0 ; i < (int) fac[v].size(); ++i) {
        dp[v][i] = fac[v][i];
        for (auto nv : g[v]) {
            if (nv == pre) continue;
            ll curr = 0;
            for (j = 0 ; j < (int) fac[nv].size(); ++j) {
                if (__gcd(fac[v][i], fac[nv][j]) == 1) {
                    // printf("transite %d %d\n", fac[v][i], fac[nv][j]);
                    curr = max(curr, dp[nv][j]);
                }
            }

            dp[v][i] += curr;
        }

        // printf("(%d,%d)=%d\n", v, i, dp[v][i]);
    }
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        int v;
        scanf("%d", &v);
        for (j = 1; j <= v; ++j) {
            int nv;
            scanf("%d", &nv);
            g[i].push_back(nv);
        }

        int sz = sqrt(a[i]);
        for (j = 1; j <= sz; ++j) {
            if (j * j == a[i]) {
                fac[i].push_back(j);
            } else {
                if (a[i] % j == 0) {
                    fac[i].push_back(j);
                    fac[i].push_back(a[i] / j);
                }
            }
        }

        sort(fac[i].begin(), fac[i].end());
        /*for (auto v : fac[i]) {
            printf("%d ", v);
        }
        printf("\n");*/
    }
    
    dfs(1, 0);
    ll ans = 0;
    for (i = 0; i < (int) fac[1].size(); ++i) {
        ans = max(ans, dp[1][i]);
    }   

    printf("%lld\n", ans);
    return 0;
}