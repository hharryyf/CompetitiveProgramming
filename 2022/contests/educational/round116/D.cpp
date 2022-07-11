#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 500011
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

vector<int> g[MAX_SIZE];
vector<int> premn[MAX_SIZE], premx[MAX_SIZE];
vector<int> sufmn[MAX_SIZE], sufmx[MAX_SIZE];
char s[MAX_SIZE];
int N, M;

int main() {
    int i, j, T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        for (i = 0; i < N; ++i) {
            g[i].clear();
            premn[i].clear();
            sufmn[i].clear();
            premx[i].clear();
            sufmx[i].clear();
            g[i] = vector<int>(M, 0);
            sufmn[i] = vector<int>(M, 0);
            premn[i] = vector<int>(M, 0);
            sufmx[i] = vector<int>(M, 0);
            premx[i] = vector<int>(M, 0);
            for (j = 0 ; j < M; ++j) {
                scanf("%d", &g[i][j]);
            }

            for (j = 0 ; j < M; ++j) {
                if (j == 0) {
                    premn[i][j] = premx[i][j] = g[i][j];
                } else {
                    premn[i][j] = min(premn[i][j-1], g[i][j]);
                    premx[i][j] = max(premx[i][j-1], g[i][j]);
                }
            }

            for (j = M - 1; j >= 0; --j) {
                if (j == M - 1) {
                    sufmx[i][j] = sufmn[i][j] = g[i][j];
                } else {
                    sufmx[i][j] = max(sufmx[i][j+1], g[i][j]);
                    sufmn[i][j] = min(sufmn[i][j+1], g[i][j]);
                }
            }
        }

        bool ok = false;
        debug("enter here\n");
        for (j = 0 ; j < M - 1; ++j) {
            multiset<int> mnL, mxL, mnR, mxR;
            vector<pair<int, int>> a;
            for (i = 0; i < N; ++i) {
                s[i] = 'R';
                mxL.insert(premn[i][j]);
                mnR.insert(sufmx[i][j+1]);
                a.emplace_back(premn[i][j], i);
            }

            sort(a.begin(), a.end());

            for (i = 0 ; i < N - 1; ++i) {
                int rowid = a[i].second;
                s[rowid] = 'B';
                mxL.erase(mxL.find(premn[rowid][j]));
                mnL.insert(premx[rowid][j]);
                mnR.erase(mnR.find(sufmx[rowid][j+1]));
                mxR.insert(sufmn[rowid][j+1]);
                if (*mxL.begin() > *mnL.rbegin() && *mxR.begin() > *mnR.rbegin()) {
                    debug("L -> %d %d\n", *mxL.begin(), *mnL.rbegin());
                    debug("R -> %d %d\n", *mxR.begin(), *mnR.rbegin());
                    ok = true;
                    printf("YES\n");
                    for (int k = 0 ; k < N; ++k) {
                        printf("%c", s[k]);
                    }

                    printf(" %d\n", j + 1);
                    break;
                }
            }

            if (ok) break;
        }

        if (!ok) {
            printf("NO\n");
        }
    }
    return 0;
}