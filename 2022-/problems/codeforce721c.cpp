#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 5011
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

inline int add(int x,int y){
    if (x + y >= mod) return mod;
    return x + y;
}

int dp[MAX_SIZE][MAX_SIZE];
int N, M;
vector<pair<int, int>> g[MAX_SIZE];
vector<int> ret;
int T;
int visited[MAX_SIZE];

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (!visited[nv.first]) {
            dfs(nv.first);
        }
    }

    ret.push_back(v);
}

int main() {
    int i, j;
    scanf("%d%d%d", &N, &M, &T);
    for (i = 1; i <= M; ++i) {
        int u, v;
        int t;
        scanf("%d%d%d", &u, &v, &t);
        g[u].emplace_back(v, t);
    } 

    for (i = 1; i <= N; ++i) {
        for (j = 0 ; j <= N; ++j) {
            dp[i][j] = mod;
        }
    }

    dp[N][0] = 0;

    dfs(1);
    
    for (i = 1; i < (int) ret.size(); ++i) {
        int v = ret[i];
        for (auto np : g[v]) {
            int nv = np.first;
            int w = np.second;
            for (j = 0; j < N; ++j) {
                if (dp[v][j + 1] > add(dp[nv][j], w)) {
                    dp[v][j + 1] = add(dp[nv][j], w);
                }
            }
        }
    }

    for (i = N ; i >= 0; --i) {
        if (dp[1][i] <= T) {
            int v = 1, step = i;
            ret.clear();
            while (v != -1) {
                ret.push_back(v);
                if (v == N) break;
                for (auto np : g[v]) {
                    int nv = np.first, w = np.second;
                    if (dp[v][step] == dp[nv][step - 1] + w) {
                        v = nv;
                        step--;
                        break;
                    }
                }
            }

            printf("%d\n", (int) ret.size());
            for (auto c : ret) {
                printf("%d ", c);
            }
            printf("\n");
            break;
        }
    }
    return 0;
}