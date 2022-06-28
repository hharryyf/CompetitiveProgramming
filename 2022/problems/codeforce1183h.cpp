#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
#define MAX_SIZE 104
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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

inline ll add(ll x,ll y){
    return min(1000000000000ll, x + y);
}


int lst[27];
ll dp[MAX_SIZE][MAX_SIZE];
char s[MAX_SIZE];
int N;
ll K;

int main() {
    int i, j, k;
    scanf("%d%lld", &N, &K);
    scanf("%s", s + 1);
    for (i = 1; i <= N; ++i) {
        dp[i][1] = 1;
        lst[s[i] - 'a'] = i;
    }

    for (j = 2; j <= N; ++j) {
        memset(lst, 0, sizeof(lst));
        for (i = 1; i <= N; ++i) {
            for (k = 0; k < 26; ++k) {
                if (lst[k]) {
                    dp[i][j] = add(dp[i][j], dp[lst[k]][j-1]);
                }
            }
            lst[s[i] - 'a'] = i;
        }
    }

    vector<ll> tol(N+1);
    for (i = 0; i < 26; ++i) {
        for (j = 1; j <= N; ++j) {
            tol[j] += dp[lst[i]][j];
        }
    }

    ll ans = 0;
    tol[0] = 1;
    for (i = N; i >= 0 && K > 0; --i) {
        ans = ans + 1ll * (N - i) * min(tol[i], K);
        K = K - min(tol[i], K);
    }

    if (K > 0) {
        printf("-1\n");
    } else {
        printf("%lld\n", ans);
    }

    return 0;
}