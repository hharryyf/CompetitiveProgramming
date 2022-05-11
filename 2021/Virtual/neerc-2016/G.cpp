#include <bits/stdc++.h>
#define SUBMIT
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE], h[MAX_SIZE];
int N, M, deg[MAX_SIZE], cnt[MAX_SIZE];
int wl[MAX_SIZE][2], draw[MAX_SIZE][2];

int main() {
    #ifdef SUBMIT
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    #endif
    int i;
    queue<pair<int, int>> q;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        h[v].push_back(u);
        deg[u]++;
    }

    for (i = 1; i <= N; ++i) {
        if (!deg[i]) {
            draw[i][0] = draw[i][1] = 1;
            q.push(make_pair(i, 0));
            q.push(make_pair(i, 1));
        }
        cnt[i] = deg[i];
    }

    /*
        Calculate the must not draw case
    */

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (auto v : h[p.first]) {
            if (p.second == 0 && !draw[v][1]) {
                /* 
                    if the first player enters a none draw position
                */
                draw[v][1] = 1;
                q.push(make_pair(v, 1));
            } else if (p.second == 1) {
                /*
                    if the second player enters a none draw position
                */
                cnt[v]--;
                if (!cnt[v]) {
                    q.push(make_pair(v, 0));
                    draw[v][0] = 1;
                }
            }
        }
    }

    // all must none draw have been eliminated at this point

    for (i = 1; i <= N; ++i) {
        if (!deg[i]) {
            wl[i][0] = 1;
            q.push(make_pair(i, 0));
        }

        if (!draw[i][0]) wl[i][0] = -1;
        if (!draw[i][1]) wl[i][1] = -1;
        cnt[i] = deg[i]; 
    }
    
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (auto v : h[p.first]) {
            if (p.second == 0 && !wl[v][1]) {
                wl[v][1] = 1;
                q.push(make_pair(v, 1));
            } else if (p.second == 1 && !wl[v][0]) {
                cnt[v]--;
                if (!cnt[v]) {
                    q.push(make_pair(v, 0));
                    wl[v][0] = 1;
                }
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        if (!draw[i][0]) {
            printf("%c", 'D');
        } else if (!wl[i][0]) {
            printf("%c", 'W');
        } else {
            printf("%c", 'L');
        }
    }
    printf("\n");

    for (i = 1; i <= N; ++i) {
        if (wl[i][1] > 0) {
            printf("%c", 'W');
        } else if (draw[i][1]) {
            printf("%c", 'L');
        } else {
            printf("%c", 'D');
        }
    }
    printf("\n");
    return 0;
}