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

map<int, vector<array<int, 4>>> mp;
int eat[MAX_SIZE][2];

int solve(vector<array<int, 4>> &dish) {
    vector<pair<pair<int, int>, array<int, 4>>> evt;
    int ret = 0, idx = -1, curr = 0;
    debug("solve group %d\n", dish[0][0] + dish[0][1] - dish[0][2]);
    for (auto &d : dish) {
        int a = d[0], b = d[1], m = d[2], id = d[3];
        // suppose the amount of b remaining is b', the amount of b we eat is b - b'
        // the amount of a we eat is m - (b - b'), hence a' = a + b - b' - m
        // b - b' <= m and a + b - b' - m >= 0
        // b' >= b - m and b' <= a + b - m
        // b - m <= b' <= a + b - m
        debug("%d has interval [%d,%d]\n", id, max(b - m, 0), min(a + b - m, b));
        evt.push_back(make_pair(make_pair(min(a + b - m, b), max(b - m, 0)), d));
    }

    sort(evt.begin(), evt.end());
    int r = -1;
    for (auto e : evt) {
        int a = e.second[0], b = e.second[1], m = e.second[2], id = e.second[3];
        
        if (r < e.first.second) {
            ret++;
            r = e.first.first;
        }

        int targetb = r;
        eat[id][1] = b - targetb;
        eat[id][0] = m - (b - targetb);    
    }

    return ret;
}

vector<array<int, 3>> input;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N;
        scanf("%d", &N);
        set<pair<int, int>> res;
        mp.clear();
        for (int i = 1; i <= N; ++i) {
            int a, b, m;
            scanf("%d%d%d", &a, &b, &m);
            mp[a + b - m].push_back({a, b, m, i});
            #ifdef D
                input.push_back({a, b, m});
            #endif
        }

        int ans = 0, targetb = -1;
        for (auto &iter : mp) {
            ans =  ans + solve(iter.second);
        }

        printf("%d\n", ans);
        for (int i = 1; i <= N; ++i) {
            printf("%d %d\n", eat[i][0], eat[i][1]);
            #ifdef D
            res.insert(make_pair(input[i-1][0] - eat[i][0], input[i-1][1] - eat[i][1]));
            #endif
        }

        #ifdef D
            if (ans != (int) res.size()) {
                printf("wrong answer\n");
                printf("failing case: ans=%d, expected=%d\n", ans, (int) res.size());
                printf("%d\n", N);
                for (auto v : input) {
                    printf("%d %d %d\n", v[0], v[1], v[2]);
                }
                return 0;
            }
            input.clear();
        #endif
    }
    return 0;
}