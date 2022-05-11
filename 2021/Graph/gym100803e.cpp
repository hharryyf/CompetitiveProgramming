#include <bits/stdc++.h>
#define MAX_SIZE 54
using namespace std;

struct state {
    int x, y, d, dir;
    state(int x, int y, int d, int dir) : x(x), y(y), d(d), dir(dir) {}
};

int N, D, T;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int ok[MAX_SIZE][MAX_SIZE][12][4];
int g[MAX_SIZE][MAX_SIZE][4];
map<char, int> mp;
vector<state> pre;
vector<pair<int, int>> ans;

void BFS(int t_d, int t_dir) {
    queue<state> q;
    int i;
    for (auto s : pre) {
        if (s.d == 0) q.push(s);
    }

    for (auto s : pre) {
        if (s.d != 0) q.push(s);
    }

    pre.clear();
    memset(ok, 0, sizeof(ok));
    while (!q.empty()) {
        auto s = q.front();
        q.pop();
        if (s.d > t_d || ok[s.x][s.y][s.d][s.dir]) continue;
        ok[s.x][s.y][s.d][s.dir] = 1;
        if (s.d == t_d && s.dir == t_dir) {
            pre.push_back(state(s.x, s.y, 0, s.dir));
            continue;
        }

        for (i = 0 ; i < 4; ++i) {
            int tx = s.x + dx[i], ty = s.y + dy[i];
            if (i == (s.dir + 2) % 4 || !g[s.x][s.y][i]) continue;
            if (t_dir == i && s.d == t_d) {
                pre.push_back(state(tx, ty, 1, t_dir));
                continue;
            }

            if (!ok[tx][ty][s.d + 1][i]) {
                q.push(state(tx, ty, s.d + 1, i));
            }
        }
    }
}

char s[4];

int main() {
    int i, j, X, Y;
    scanf("%d%d%d%d", &N, &X, &Y, &T);
    mp['N'] = 0, mp['S'] = 2, mp['E'] = 1, mp['W'] = 3;
    for (i = 0 ; i < N; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            if (y1 > y2) swap(y1, y2);
            for (j = y1; j < y2; ++j) {
                g[x1][j][0] = g[x1][j + 1][2] = 1;
            }
        } else {
            if (x1 > x2) swap(x1, x2);
            for (j = x1; j < x2; ++j) {
                g[j][y1][1] = g[j+1][y1][3] = 1;
            }
        }
    }

    pre.push_back(state(X, Y, 0, 0));
    pre.push_back(state(X, Y, 0, 1));
    pre.push_back(state(X, Y, 0, 2));
    pre.push_back(state(X, Y, 0, 3));
    for (i = 0 ; i < T; ++i) {
        int d;
        scanf("%d%s", &d, s);
        BFS(d, mp[s[0]]);
    } 
    
    for (auto s : pre) {
        if (s.d == 1) {
            ans.emplace_back(s.x - dx[s.dir], s.y - dy[s.dir]);
        } else {
            ans.emplace_back(s.x, s.y);
        }
    }

    
    sort(ans.begin(), ans.end());

    for (i = 0 ; i < (int) ans.size(); ++i) {
        if (i == 0 || ans[i].first != ans[i-1].first || ans[i].second != ans[i-1].second) {
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
    }

    return 0;
}