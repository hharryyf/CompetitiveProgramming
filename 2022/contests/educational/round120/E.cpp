#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 524312
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

const ll mod = 1e9 + 7;

inline ll add(ll x,ll y){
    return ((x + y) % mod + mod) % mod;
}

inline ll mul(ll x,ll y){
    return x * y % mod;
}

inline ll qpow(ll x,ll n){
    ll ret= 1;
    while(n > 0){
        if(n & 1) ret = mul(ret, x);
        x = mul(x, x);
        n >>= 1;
    }

    return ret;
}

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int N, M;

int x[11];
int problem[10011];
char s[11][10011];

int main() {
    int T, i, j, k;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        for (i = 0; i < N; ++i) {
            scanf("%d", &x[i]);
        }

        for (i = 0; i < N; ++i) {
            scanf("%s", s[i]);
        }

        int ans = 0, bestbt = 0;
        for (i = 0 ; i < (1 << N); ++i) {
            // bt set to 0 means x - r
            // bt set to 1 means r - x
            for (j = 0 ; j < M; ++j) problem[j] = 0;
            int score = 0;
            for (j = 0; j < N; ++j) {
                if ((i >> j) & 1) {
                    for (k = 0 ; k < M; ++k) {
                        if (s[j][k] == '1') {
                            problem[k]--;
                        }
                    }
                } else {
                    for (k = 0 ; k < M; ++k) {
                        if (s[j][k] == '1') {
                            problem[k]++;
                        }
                    }
                }
            }

            vector<pair<int, int>> rt;
            for (j = 0 ; j < M; ++j) {
                rt.emplace_back(problem[j], j);
            }

            sort(rt.begin(), rt.end());

            for (j = 0 ; j < M; ++j) {
                problem[rt[j].second] = j + 1;
            }

            for (j = 0; j < N; ++j) {
                int curr = 0;
                for (k = 0 ; k < M; ++k) {
                    if (s[j][k] == '1') {
                        curr += problem[k];
                    }
                }

                score += abs(curr - x[j]);
            }

            if (score > ans) {
                ans = score;
                bestbt = i;
            }
        }        

        for (j = 0 ; j < M; ++j) problem[j] = 0;
        for (j = 0; j < N; ++j) {
            if ((bestbt >> j) & 1) {
                for (k = 0 ; k < M; ++k) {
                    if (s[j][k] == '1') {
                        problem[k]--;
                    }
                }
            } else {
                for (k = 0 ; k < M; ++k) {
                    if (s[j][k] == '1') {
                        problem[k]++;
                    }
                }
            }
        }

        vector<pair<int, int>> rt;
        for (j = 0 ; j < M; ++j) {
            rt.emplace_back(problem[j], j);
        }

        sort(rt.begin(), rt.end());

        for (j = 0 ; j < M; ++j) {
            problem[rt[j].second] = j + 1;
        }

        for (j = 0 ; j < M; ++j) {
            printf("%d ", problem[j]);
        }

        printf("\n");
    }
    return 0;
}