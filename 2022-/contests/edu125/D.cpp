/*
    i: n_i
    (1) n_i * c_i <= C
    (2) H_j / (d_i * n_i) < h_i / D_j
        H_j * D_j < h_i * (d_i * n_i)
        n_i = ceil((H_j * D_j) / (h_i * d_i))
    ans = min ceil((H_j * D_j) / (h_i * d_i)) * c_i
    let A_j = H_j * D_j, B_i = h_i * d_i
    ans = min ceil(A_j / B_i) * c_i
    if ans > C --> -1
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define MAX_SIZE 1000111
int N;
ll C;

ll r[MAX_SIZE], maxr[MAX_SIZE];

int main() {
    int i, j, Q;
    scanf("%d%lld", &N, &C);
    for (i = 1; i <= N; ++i) {
        ll c, d, h;
        scanf("%lld%lld%lld", &c, &d, &h);
        r[c] = max(r[c], d * h);
    }

    for (i = 1; i <= C; ++i) {
        for (j = 1; j * i <= C; ++j) {
            maxr[i * j] = max(maxr[i * j], r[i] * j);
        }
    }

    for (i = 1; i <= C; ++i) maxr[i] = max(maxr[i], maxr[i - 1]);

    vector<ll> res = vector<ll>(C + 1, 0ll);
    for (i = 1; i <= C; ++i) res[i] = maxr[i];
    sort(res.begin(), res.end());
    /*for (auto r : res) {
        cout << r << endl;
    }*/
    scanf("%d", &Q);
    while (Q-- > 0) {
        ll D, H;
        scanf("%lld%lld", &D, &H);
        if (maxr[C] <= D * H) {
            printf("-1 ");
            
        } else {
            int idx = upper_bound(res.begin(), res.end(), D * H) - res.begin();
            printf("%d ", idx);
        }

    }
    return 0;
}