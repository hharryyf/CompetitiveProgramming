#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[8][129];
int num[8], N, r;

void init() {
    int i, j;
    for (i = 0 ; i < 8; ++i) {
        for (j = 0 ; j < 129; ++j) {
            dp[i][j] = 0;
        }
        num[i] = 0;
    }
}

int main() {
    int i, j, k, l;
    while (scanf("%d", &r) != EOF) {
        init();
        //printf("we get %d\n", r);
        int sz = -1;
        while (r-- > 0) {
            int v;
            scanf("%d", &v);
            if (sz == -1) sz = v;
            for (i = 1; i <= v; ++i) {
                num[i]++;
            }  
        }

        scanf("%d", &N);
        //printf("we get N= %d\n", N);
        dp[0][(1 << N) - 1] = 1;
        num[0] = N;
        for (i = 0 ; i < sz; ++i) {
            for (j = 0 ; j <= (1 << N) - 1; ++j) {
                if (__builtin_popcount(j) != num[i]) continue;
                for (k = 0; k <= (1 << N) - 1; ++k) {
                    if (__builtin_popcount(k) != num[i+1]) continue;
                    vector<int> L, R;
                    for (l = 0 ; l < N; ++l) {
                        if ((1 << l) & j) {
                            L.push_back(l);
                        }

                        if ((1 << l) & k) {
                            R.push_back(l);
                        }
                    } 

                    bool valid = true;
                    // cout << L.size() << " " << R.size() << endl;
                    for (l = 0 ; l < (int) R.size(); ++l) {
                        if (R[l] < L[l]) {
                            valid = false;
                            break;
                        }
                    }

                    if (valid) {
                        dp[i+1][k] += dp[i][j];
                        //cout << "add " << (i + 1) << " " << k << " to " << dp[i+1][k] << endl; 
                    }
                }
            }
        }

        ll ans = 0;
        for (i = 0; i <= (1 << N) - 1; ++i) {
            ans += dp[sz][i];
        }

        printf("%lld\n", ans);
    }
    return 0;
}