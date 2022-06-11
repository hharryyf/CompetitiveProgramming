#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200011
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

int N;

vector<int> g[MAX_SIZE];

int solve(vector<pair<int, int>> &itv) {
    if ((int) itv.size() == 1 && itv[0].first == itv[0].second) return 1;
    int ret = 2, r = itv[0].second, pivot = itv[0].second, i = 0, j = 0;
    int mx = 0;
    for (auto p : itv) mx = max(mx, p.second);
    while (r < mx) {
        while (j < (int) itv.size() && itv[j].first <= pivot) {
            r = max(r, itv[j].second);
            ++j;
        } 

        pivot = r;
        ret++;
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        g[v].push_back(i);
    }

    vector<pair<int, int>> itv;
    for (int i = 1; i <= N; ++i) {
        if (!g[i].empty()) {
            itv.emplace_back(g[i].front(), g[i].back());
        }
    }

    sort(itv.begin(), itv.end());
    vector<pair<int, int>> curr;
    int ans = 0, r = 0;
    for (auto it : itv) {
        if (it.first > r) {
            if (!curr.empty()) {
                ans += solve(curr);
                curr.clear();
            }
        }

        curr.emplace_back(it.first, it.second);
        r = max(r, it.second);
    }

    if (!curr.empty()) ans = ans + solve(curr);


    printf("%d\n", N - ans);
    return 0;
}