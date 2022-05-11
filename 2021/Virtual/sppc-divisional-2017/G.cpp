#include <bits/stdc++.h>

using namespace std;

int C[7], amt[7] = {1, 2, 5, 10, 20, 50};
int D[7], e[7],  CC[7];

int main() {
    int i, ans = 0;
    for (i = 0 ; i < 6; ++i) {
        scanf("%d", &C[i]);
        D[i] = C[i];
    }

    int T, k;
    scanf("%d", &T);
    while (T-- > 0) {
        int V, rem = 0;
        scanf("%d", &V);
        for (i = 0 ; i < 6; ++i) {
            scanf("%d", &e[i]);
            rem += e[i] * amt[i];
            C[i] += e[i];
            CC[i] = C[i];
        }
        rem -= V;
        int tol = rem + 52, orrem = rem;
        //cout << "change " << rem << endl;
        for (k = rem; k <= tol; ++k) {
            int crem = k;
            for (i = 0 ; i < 6; ++i) C[i] = CC[i];
            bool valid = true;
            while (crem != 0) {
                for (i = 5; i >= 0; --i) {
                    if (crem >= amt[i]) {
                        int change = min(crem / amt[i], C[i]);
                        crem -= change * amt[i];
                        C[i] -= change;
                        if (crem >= amt[i]) {
                            valid = false;
                            break;
                        }
                        break;
                    }
                }

                if (!valid) break;
            }

            if (valid) {
                // cout << "check ok " << k << endl;
                ans += k - orrem;
                if (k != orrem) {
                    for (i = 0 ; i < 6; ++i) {
                        C[i] = D[i];
                    }
                }
                break;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}