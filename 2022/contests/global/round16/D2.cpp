#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 311
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

pair<int, int> a[MAX_SIZE][MAX_SIZE];
// a value --> (row, col)
// ordered by col first in decreasing order, then row in ascending order
// (-col, row)
map<int, vector<pair<int, int>>> pos;
map<int, vector<int>> ord;

int main() {
    int T;
    scanf("%d", &T); 
    while (T-- > 0) {
        int N, M;
        scanf("%d%d", &N, &M);
        pos.clear();
        ord.clear();
        vector<int> people(N * M);
        int i, j, ans = 0;
        for (i = 0 ; i < N * M; ++i) {
            scanf("%d", &people[i]);
            ord[people[i]].push_back(i);
        }

        sort(people.begin(), people.end());

        for (i = 0 ; i < N * M; ++i) {
            int rid = i / M, cid = i % M;
            pos[people[i]].emplace_back(rid, -cid);
        }

        for (auto & iter: pos) {
            sort(iter.second.begin(), iter.second.end());
            int j = 0;
            for (auto p : iter.second) {
                a[p.first][-p.second] = make_pair(iter.first, ord[iter.first][j]);
                ++j;
            }
        }

        for (i = 0 ; i < N; ++i) {
            for (j = 0; j < M; ++j) {
                for (int k = j + 1; k < M; ++k) {
                    if (a[i][j].first < a[i][k].first && a[i][j].second < a[i][k].second) ans++;
                }
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}