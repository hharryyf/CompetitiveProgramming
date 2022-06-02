#pragma GCC optimize(3)
#pragma GCC optimize(2)
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

// #define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 200011
typedef long long ll;
int f[MAX_SIZE];
ll a[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}

int main() {
    int T, N, i;
    scanf("%d", &T);
    while (T-- > 0) {
        ll ans = 0, P;
        vector<pair<ll, int>> pos;
        scanf("%d%lld", &N, &P);
        for (i = 1; i <= N; ++i) {
            scanf("%lld", &a[i]);
            f[i] = i;
            pos.emplace_back(a[i], i);
        }

        sort(pos.begin(), pos.end());

        for (auto p : pos) {
            if (p.first > P) break;
            int pp = p.second - 1;
            while (pp >= 1 && find(pp) != find(p.second) && a[pp] % p.first == 0) {
                unionset(pp, p.second);
                ans += p.first;
                pp--;
            }

            pp = p.second + 1;
            while (pp <= N && find(pp) != find(p.second) && a[pp] % p.first == 0) {
                unionset(pp, p.second);
                ans += p.first;
                pp++;
            }
        }

        for (i = 1; i < N;  ++i) {
            if (find(i) != find(i + 1)) ans += P;
        }

        printf("%lld\n", ans);
    }
    return 0;
}