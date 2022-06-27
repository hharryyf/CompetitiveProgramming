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
int parent[MAX_SIZE][18];
int a[MAX_SIZE], visited[MAX_SIZE];
vector<int> prime[MAX_SIZE];
// map from prime to position, if i is composite, vector is empty
vector<int> pos[MAX_SIZE];

int main() {
    int N, Q, i, j;
    for (i = 2; i <= 100000; ++i) {
        if (visited[i]) continue;
        for (j = 1; j * i <= 100000; ++j) {
            visited[i * j] = 1;
            prime[i * j].push_back(i);
        }
    }
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        for (auto v : prime[a[i]]) {
            pos[v].push_back(i);
        }
    }

    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = 0; j <= 17; ++j) {
            parent[i][j] = N + 1;
        }
    }

    for (i = N - 1; i >= 1; --i) {
        int mx = N + 1;
        for (auto v : prime[a[i]]) {
            if (pos[v].back() > i) {
                int p = upper_bound(pos[v].begin(), pos[v].end(), i) - pos[v].begin();
                mx = min(mx, pos[v][p]);
            }
        }

        parent[i][0] = min(parent[i+1][0], mx);
    }

    for (i = N - 1; i >= 1; --i) {
        for (j = 1; j <= 17; ++j) {
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }

    for (i = 1; i <= N; ++i) {
        debug("p[%d][0] = %d\n", i, parent[i][0]);
    }

    while (Q-- > 0) {
        int l, r;
        int ans = 1;
        scanf("%d%d", &l, &r);
        for (i = 17; i >= 0; --i) {
            if (parent[l][i] <= r) {
                l = parent[l][i];
                ans += (1 << i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}