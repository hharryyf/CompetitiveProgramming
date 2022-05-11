#include <bits/stdc++.h>

using namespace std;

set<pair<int, int>> vis;
int curr = 0, N, M;
int a[55][55];
void mark(int x, int y) {
    if (x <= 0 || y <= 0 || x > N || y > M) return;
    if (vis.find({x, y}) != vis.end()) return;
    vis.insert({x, y});
    curr += a[x][y];
}

char s[22];
int len;

int main() {
    int i, j, k, ans = 0;
    scanf("%d", &len);
    if (len != 0) {
        scanf("%s", s);
    }

    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &a[i][j]);
        }
    }

    for (i = -12; i <= N + 12; ++i) {
        for (j = -12; j <= M + 12; ++j) {
            int x = i, y = j;
            curr = 0;
            vis.clear();
            mark(x, y);
            for (k = 0; k < len; ++k) {
                if (s[k] == 'l') {
                    y--;
                } else if (s[k] == 'r') {
                    y++; 
                } else if (s[k] == 'u') {
                    x--;
                } else {
                    x++;
                }
                mark(x, y);
            }
            ans = max(ans, curr);
        }
    }

    printf("%d\n", ans);
    return 0;
}