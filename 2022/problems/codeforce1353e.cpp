#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1000111
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

const int mod = 1e9 + 7;

inline int add(int x,int y){
    return ((x + y) % mod + mod) % mod;
}

inline int mul(int x,int y){
    return (1ll * x * y) % mod;
}

int N, K;
char s[MAX_SIZE];

int solve(vector<int> &vc) {
    int cnt = 0, ans = 0, curr = 0;
    for (auto &v : vc) {
        cnt += v;
        if (v == 0) v = -1;
    }

    for (auto v : vc) {
        curr += v;
        if (curr < 0) curr = 0;
        ans = max(ans, curr);
    }

    return cnt - ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j, cnt = 0, ans;
        scanf("%d%d", &N, &K);
        ans = N;
        scanf("%s", s + 1);
        for (i = 1; i <= N; ++i) {
            if (s[i] == '1') cnt++;
        }

        for (i = 1; i <= K; ++i) {
            vector<int> vc;
            int cnt2 = 0;
            for (j = i; j <= N; j = j + K) {
                vc.push_back(s[j] - '0');
                if (vc.back() == 1) {
                    cnt2++;
                }
            }

            ans = min(ans, solve(vc) + (cnt - cnt2));
        }

        printf("%d\n", ans);
    }
    return 0;
}