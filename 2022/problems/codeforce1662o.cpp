#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 8351
bool wall[23][363];
bool circle[23][363];
int visited[MAX_SIZE];
char tp[3];
vector<int> g[MAX_SIZE];

int idx(int r, int theta) {
    return r * 360 + theta;
}

void addedge(int v1, int v2) {
    g[v1].push_back(v2);
    g[v2].push_back(v1);
}

void dfs(int v) {
    if (visited[v]) return;
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            dfs(nv);
        } 
    } 
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j;
        scanf("%d", &N);
        // init
        memset(wall, false, sizeof(wall));
        memset(circle, false, sizeof(circle));
        memset(visited, 0, sizeof(visited));
        for (i = 0; i < MAX_SIZE; ++i) g[i].clear();
        // read input
        for (j = 0; j < N; ++j) {
            int v1, v2, v3;
            scanf("%s%d%d%d", tp, &v1, &v2, &v3);
            if (tp[0] == 'C') {
                if (v2 > v3) v3 += 360;
                for (i = v2; i < v3; ++i) {
                    circle[v1][(i + 360) % 360] = true;
                }
            } else {
                for (i = v1; i < v2; ++i) {
                    wall[i][v3] = true;
                }
            }
        }

        // construct the graph
        for (i = 0; i <= 21; ++i) {
            for (j = 0; j < 360; ++j) {
                // consider the circular walls
                if (i < 21 && !circle[i+1][j]) {
                    addedge(idx(i, j), idx(i + 1, j));
                }

                // consider the normal walls
                if (!wall[i][j]) {
                    addedge(idx(i, j), idx(i, (j - 1 + 360) % 360));
                }
            }
        }

        // solve
        for (i = 0; i < 360; ++i) {
            if (!visited[idx(0, i)]) {
                dfs(idx(0, i));
            }
        }

        // judge
        bool ret = false;
        for (i = 0 ; i < 360; ++i) {
            if (visited[idx(21, i)]) {
                ret = true;
                break;
            }
        }

        printf("%s\n", ret ? "YES" : "NO");
    }
    return 0;
}