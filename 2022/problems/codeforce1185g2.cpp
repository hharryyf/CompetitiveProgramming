#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 52
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

int cnt12[MAX_SIZE][MAX_SIZE][MAX_SIZE * MAX_SIZE];
int cnt3[MAX_SIZE][MAX_SIZE * MAX_SIZE];
int cnt[MAX_SIZE][MAX_SIZE][MAX_SIZE][3];
int dp[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int fac[MAX_SIZE];
int N, T;
vector<int> a[3];


int main() {
    int i, j, k;
    scanf("%d%d", &N, &T);
    fac[0] = 1;
    for (i = 1; i < MAX_SIZE; ++i) {
        fac[i] = mul(fac[i-1], i);
    }

    for (i = 1; i <= N; ++i) {
        int t, g;
        scanf("%d%d", &t, &g);
        g--;
        a[g].push_back(t);
    }

    int N1 = a[0].size(), N2 = a[1].size(), N3 = a[2].size();
    cnt[1][0][0][0] = cnt[0][1][0][1] = cnt[0][0][1][2] = 1;

    for (i = 0; i <= N1; ++i) {
        for (j = 0; j <= N2; ++j) {
            for (k = 0 ; k <= N3; ++k) {
                cnt[i+1][j][k][0] = add(cnt[i+1][j][k][0], add(cnt[i][j][k][1], cnt[i][j][k][2]));
                cnt[i][j+1][k][1] = add(cnt[i][j+1][k][1], add(cnt[i][j][k][0], cnt[i][j][k][2]));
                cnt[i][j][k+1][2] = add(cnt[i][j][k+1][2], add(cnt[i][j][k][0], cnt[i][j][k][1]));
            }
        }
    }

    for (i = 0; i <= N1; ++i) {
        for (j = 0 ; j <= N2; ++j) {
            for (k = 0 ; k <= N3; ++k) {
                dp[i][j][k] = add(cnt[i][j][k][0], add(cnt[i][j][k][1], cnt[i][j][k][2]));
                dp[i][j][k] = mul(dp[i][j][k], mul(fac[i], mul(fac[j], fac[k])));
                debug("dp[%d][%d][%d] = %d\n", i, j, k, dp[i][j][k]);
            }
        }
    }

    // at this point we've already solved the problem given i type 1, j type 2, k type 3, what's the total arrangement
    // we only need to find which how many of each (i, j, k) combination exists
    cnt12[0][0][0] = 1;
    cnt3[0][0] = 1;
    for (auto t : a[0]) {
        for (i = N1; i >= 0; --i) {
            for (j = N2; j >= 0; --j) {
                for (k = T; k >= 0; --k) {
                    if (i + 1 <= N1 && k + t <= T) {
                        cnt12[i + 1][j][k + t] = add(cnt12[i+1][j][k + t], cnt12[i][j][k]);
                    } 
                }
            }
        }
    }

    for (auto t : a[1]) {
        for (i = N1; i >= 0; --i) {
            for (j = N2; j >= 0; --j) {
                for (k = T; k >= 0; --k) {
                    if (j + 1 <= N2 && k + t <= T) {
                        cnt12[i][j + 1][k + t] = add(cnt12[i][j + 1][k + t], cnt12[i][j][k]);
                    } 
                }
            }
        }
    }

    for (auto t : a[2]) {
        for (i = N3; i >= 0; --i) {
            for (k = T; k >= 0; --k) {
                if (i + 1 <= N3 && k + t <= T) {
                    cnt3[i + 1][k + t] = add(cnt3[i+1][k + t], cnt3[i][k]);
                } 
            }
        }
    }

    int ans = 0;
    for (i = 0 ; i <= N1; ++i) {
        for (j = 0 ; j <= N2; ++j) {
            for (k = 0; k <= N3; ++k) {
                for (int l = 0; l <= T; ++l) {
                    int way = dp[i][j][k];
                    ans = add(ans, mul(way, mul(cnt12[i][j][l], cnt3[k][T - l])));    
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}