#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

int N, M, K;

char pattern[MAX_SIZE][5], constraint[MAX_SIZE][5];
int early[MAX_SIZE], visited[MAX_SIZE];
map<string, int> mp;
vector<int> g[MAX_SIZE];
vector<int> ret;
bool cycle = false;

void dfs(int v) {
    visited[v] = 1;
    for (auto nv : g[v]) {
        if (visited[nv] == 1) cycle = true;
        if (!visited[nv]) {
            dfs(nv);
        }
    }
    ret.push_back(v);
    visited[v] = 2;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= N; ++i) {
        scanf("%s", pattern[i]);
        mp[string(pattern[i])] = i;
    }

    for (int i = 1; i <= M; ++i) {
        scanf("%s%d", constraint[i], &early[i]);
        for (int j = 0; j < K; ++j) {
            if (constraint[i][j] != pattern[early[i]][j] && pattern[early[i]][j] != '_') {
                printf("NO\n");
                return 0;
            }
        }
    }
    for (int i = 1; i <= M; ++i) {
        for (int j = 0 ; j < (1 << K); ++j) {
            string s = string(constraint[i]);
            for (int k = 0; k < K; ++k) {
                if ((j >> k) & 1) {
                    continue;
                } else {
                    s[k] = '_';
                }
            }

            if (mp.find(s) != mp.end()) {
                if (early[i] == mp[s]) continue;
                g[early[i]].push_back(mp[s]);
                debug("add edge %d --> %d\n", early[i], mp[s]);
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) dfs(i);
    }

    reverse(ret.begin(), ret.end());

    if (cycle) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    for (auto v : ret) {
        printf("%d ", v);
    }
    printf("\n");
    return 0;
}