#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 20000111
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

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int N, M, cnt;
bool st[MAX_SIZE];
int visited[MAX_SIZE / 20];

void update(int idx) {
    if (!st[idx]) cnt++;
    st[idx] = 1;
}

ll tol[22];
vector<pair<int, int>> prime[MAX_SIZE / 20];

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    assert (N >= 1 && M >= 1);
    for (i = 1; i <= 20; ++i) {
        for (j = 1; j <= M; ++j) {
            update(i * j);
        }
        tol[i] = cnt;
    }

    for (i = 2; i <= 1000000; ++i) {
        if (!visited[i]) {
            for (j = 1; j * i <= 1000000; ++j) {
                visited[i * j] = 1;
                prime[i * j].emplace_back(i, 0);
            }
        }
    }

    ll ans = 1;
    for (i = 2; i <= N; ++i) {
        for (auto &p : prime[i]) {
            int v = i;
            while (v % p.first == 0) {
                p.second++;
                v = v / p.first;
            }
        }

        int fc = 0;
        for (auto &p : prime[i]) {
            fc = gcd(fc, p.second);
        }

        if (fc == 1) {
            int v = i, ct = 1;
            while (1ll * v * i <= N) {
                v = v * i;
                ct++;
            }

            ans = ans + tol[ct];
            debug("at i=%d + %lld\n", i, tol[ct]);
        }
    }

    printf("%lld\n", ans);
    return 0;
}