#include <bits/stdc++.h>
#define MAX_SIZE 100011
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
using namespace std;

set<int> tree[MAX_SIZE * 3];
vector<pair<pair<int, int>, int>> add[MAX_SIZE];
vector<pair<pair<int, int>, int>> del[MAX_SIZE];
string s[MAX_SIZE];
vector<int> dist[MAX_SIZE];
vector<int> visited[MAX_SIZE];
vector<int> timestp[MAX_SIZE];
char ss[MAX_SIZE];
const int inf = 1e9 + 7;
int N, M, K;

int dx[8] = {1, 0, 0, -1, 1, 1, -1, -1};
int dy[8] = {0, -1, 1, 0, 1, -1, 1, -1};

int valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

void update(int start, int end, int l, int r, int index, int tp) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        if (tp > 0) {
            tree[index].insert(tp);
        } else {
            tree[index].erase(-tp);
        }
        return;
    }

    if (end <= MID) update(start, end, l, MID, LEFT, tp);
    else if (start >= MID + 1) update(start, end, MID + 1, r, RIGHT, tp);
    else {
        update(start, end, l, MID, LEFT, tp);
        update(start, end, MID + 1, r, RIGHT, tp);
    }
}

int query(int pt, int l, int r, int index) {
    if (l > r || pt < l || pt > r) return inf;
    int curr = tree[index].empty() ? inf : *tree[index].begin();
    if (l == r) return curr;
    if (pt <= MID) return min(curr, query(pt, l, MID, LEFT));
    return min(query(pt, MID + 1, r, RIGHT), curr); 
}

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &K);
    for (i = 0 ; i < N; ++i) {
        scanf("%s", ss);
        s[i] = string(ss);
    }

    for (i = 0 ; i < N; ++i) {
        dist[i] = vector<int>(M, inf);
        timestp[i] = vector<int>(M, inf);
        visited[i] = vector<int>(M, 0);
    }

    queue<pair<int, int>> q;

    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < M; ++j) {
            if (s[i][j] == 'S') {
                q.push({i, j});
                dist[i][j] = 0;
            }

            if (s[i][j] == 'X') {
                timestp[i][j] = 0;
            }
        }
    }

    for (i = 1 ; i <= K; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1--, y1--, x2--, y2--;
        add[x1].push_back(make_pair(make_pair(y1, y2), i));
        del[x2].push_back(make_pair(make_pair(y1, y2), i));
    }

    for (i = 0 ; i < N; ++i) {
        for (auto p : add[i]) {
            update(p.first.first, p.first.second, 0, M - 1, 1, p.second);           
        }

        for (j = 0 ; j < M; ++j) {
            timestp[i][j] = min(timestp[i][j], query(j, 0, M - 1, 1));
        }

        for (auto p : del[i]) {
            update(p.first.first, p.first.second, 0, M - 1, 1, -p.second);
        }
    }

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        visited[p.first][p.second] = 1;
        for (i = 0 ; i < 8; ++i) {
            int tx = dx[i] + p.first;
            int ty = dy[i] + p.second;
            if (valid(tx, ty) && !visited[tx][ty] && timestp[tx][ty] > dist[p.first][p.second] + 1) {
                if (dist[tx][ty] > dist[p.first][p.second] + 1) {
                    dist[tx][ty] = dist[p.first][p.second] + 1;
                    q.push({tx, ty});
                }
            }
        }
    }
    /*
    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < M; ++j) {
            printf("%d ", timestp[i][j]);
        }
        printf("\n");
    }*/

    for (i = 0 ; i < N; ++i) {
        for (j = 0 ; j < M; ++j) {
            if (timestp[i][j] > K && dist[i][j] <= K) {
                printf("%d %d\n", i + 1, j + 1);
                return 0;
            }
        }
    }   

    printf("-1\n");
    return 0;
}