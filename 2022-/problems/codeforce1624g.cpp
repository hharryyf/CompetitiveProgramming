#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 262192
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
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
using namespace std;
typedef long long ll;

struct edge {
    int from, to, wt;
};

int N, M;
int f[MAX_SIZE];
edge edg[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    f[fx] = fy;
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        int res = 0, bad = 0;
        scanf("%d%d", &N, &M);
        for (i = 1; i <= N; ++i) f[i] = i;
        for (i = 1; i <= M; ++i) scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].wt);
        for (j = 30; j >= 0; --j) {
            for (i = 1; i <= N; ++i) f[i] = i;
            for (i = 1; i <= M; ++i) {
                if ((edg[i].wt >> j) & 1) continue;
                if (bad & edg[i].wt) continue;
                unionset(edg[i].from, edg[i].to);
            }

            int cnt = 0;
            for (i = 1; i <= N; ++i) {
                if (find(i) == i) cnt++;
            }

            if (cnt > 1) {
                res |= (1 << j);
            } else {
                bad |= (1 << j);
            }
        }

        printf("%d\n", res);
    }
    return 0;
}