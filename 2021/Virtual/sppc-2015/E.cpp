#include <bits/stdc++.h>
using namespace std;

vector<int> bpt;
vector<int> qpt;
vector<int> tmp, disc;
int Q, N, L, A, B;

int nxt(int g) {
    return (1ll * A * g + B) % (L + 1);
}

int main() {
    int i, j, k;
    scanf("%d%d%d%d%d", &Q, &N, &L, &A, &B);
    bpt = vector<int>(N + 1, 0);
    scanf("%d", &bpt[1]);
    qpt = vector<int>(Q, 0);
    for (i = 0; i < Q; ++i) {
        scanf("%d", &qpt[i]);
        qpt[i]--;
    }
    for (i = 2; i <= N; ++i) {
        bpt[i] = nxt(bpt[i-1]);
    }

    for (auto v : bpt) tmp.push_back(v);
    for (auto v : qpt) tmp.push_back(v);
    sort(bpt.begin(), bpt.end());
    /*for (auto v : bpt) {
        printf("%d ", v);
    }
    printf("\n");*/
    sort(tmp.begin(), tmp.end());
    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    int mx = 0, pg = 0;
    for (i = 0, j = 0, k = 0 ; i < (int) disc.size(); ++i) {
        while (j < (int) bpt.size() && bpt[j] <= disc[i]) {
            mx = max(mx, bpt[j] - pg - 1);
            pg = bpt[j++];
        }

        while (k < (int) qpt.size() && qpt[k] <= disc[i]) {
            printf("%d\n", max(qpt[k] - pg, mx));
            ++k;
        }
    }
    return 0;
}