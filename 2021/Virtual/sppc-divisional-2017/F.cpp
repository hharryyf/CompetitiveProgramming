#include <bits/stdc++.h>

using namespace std;

int N, H;
int dx[3] = {-1, 0, 1};
int P[3];
double p[2][101];

int fix(int x) {
    if (x < 0) return 0;
    if (x > H) return H;
    return x;
}

int main() {
    int i, j, a, k;
    double ans = 0;
    cin >> N >> H >> a >> P[0] >> P[1] >> P[2];
    p[0][a] = 1;
    ans += 0.5 * a;
    for (i = 0; i < N; ++i) {
        int nxt = (i + 1) & 1, cur = i & 1;
        for (j = 0 ; j <= H; ++j) p[nxt][j] = 0;
        for (j = 0; j <= H; ++j) {
            for (k = 0 ; k < 3; ++k) {
                int h = fix(dx[k] + j);
                p[nxt][h] += 0.01 * p[cur][j] * P[k];
                // E[nxt][h] += p[nxt][h] * (E[cur][j] + 0.5 * (h + j) * p[cur][j]);
            }
        }

        for (j = 0 ; j <= H; ++j) {
            if (i != N - 1) {
                ans += p[nxt][j] * j;
            } else {
                ans += p[nxt][j] * j * 0.5;
            }
        }
        //cout << endl;
    }

    printf("%.10lf\n", ans);
    return 0;
}