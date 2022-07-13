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

int N, M;
int H[MAX_SIZE];
int V[MAX_SIZE];
int x[MAX_SIZE], y[MAX_SIZE];
vector<int> discx, discy;
int prex[MAX_SIZE], prey[MAX_SIZE];
vector<int> gh[MAX_SIZE], gv[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, K;
        set<int> hasV, hasH;
        discx.clear();
        discy.clear();
        scanf("%d%d%d", &N, &M, &K);
        vector<int> tmpx, tmpy;
        for (i = 1; i <= N; ++i) {
            scanf("%d", &V[i]);
            tmpx.push_back(V[i]);
        }
        
        for (i = 1; i <= M; ++i) {
            scanf("%d", &H[i]);
            tmpy.push_back(H[i]);
        }

        for (i = 1; i <= K; ++i) {
            scanf("%d%d", &x[i], &y[i]);
            tmpx.push_back(x[i]);
            tmpy.push_back(y[i]);
        }

        sort(tmpx.begin(), tmpx.end());
        sort(tmpy.begin(), tmpy.end());

        for (i = 0 ; i < (int) tmpx.size(); ++i) {
            if (i == 0 || tmpx[i] != tmpx[i-1]) discx.push_back(tmpx[i]);
        }

        for (i = 0 ; i < (int) tmpy.size(); ++i) {
            if (i == 0 || tmpy[i] != tmpy[i-1]) discy.push_back(tmpy[i]);
        }

        for (i = 1; i <= N; ++i) {
            int idx = lower_bound(discx.begin(), discx.end(), V[i]) - discx.begin() + 1;
            V[i] = idx;
            hasV.insert(idx);
        }

        for (i = 1; i <= M; ++i) {
            int idx = lower_bound(discy.begin(), discy.end(), H[i]) - discy.begin() + 1;
            H[i] = idx;
            hasH.insert(idx);
        }

        for (i = 1; i <= K; ++i) {
            int idx = lower_bound(discx.begin(), discx.end(), x[i]) - discx.begin() + 1;
            x[i] = idx;
            idx = lower_bound(discy.begin(), discy.end(), y[i]) - discy.begin() + 1;
            y[i] = idx;
        }

        int xsz = discx.size(), ysz = discy.size();

        for (i = 1; i <= xsz; ++i) {
            prex[i] = 0;
        }

        for (i = 1; i <= ysz; ++i) {
            prey[i] = 0;
        }

        for (i = 1; i <= xsz; ++i) {
            gv[i].clear();
        }

        for (i = 1; i <= ysz; ++i) {
            gh[i].clear();
        }

        for (i = 1; i <= K; ++i) {
            gv[x[i]].push_back(y[i]);
            gh[y[i]].push_back(x[i]);
            prex[x[i]]++;
            prey[y[i]]++;
        }

        for (i = 1; i <= xsz; ++i) {
            prex[i] += prex[i-1];
            sort(gv[i].begin(), gv[i].end());
        }

        for (i = 1; i <= ysz; ++i) {
            prey[i] += prey[i-1];
            sort(gh[i].begin(), gh[i].end());
        }

        ll ans = 0;

        for (i = 1; i <= K; ++i) {
            auto v = hasV.find(x[i]) != hasV.end();
            auto h = hasH.find(y[i]) != hasH.end();
            if (v && h) continue;
            if (v) {
                debug("calculate <%d,%d> previous answer = %lld\n", discx[x[i]-1], discy[y[i]-1], ans);
                int low = *prev(hasH.lower_bound(y[i])), high = *hasH.lower_bound(y[i]);
                ans = ans + max(prey[high - 1] - prey[low] - 1, 0);
                debug("first step ans --> %lld\n", ans);
                int id1 = upper_bound(gv[x[i]].begin(), gv[x[i]].end(), low) - gv[x[i]].begin();
                int id2 = lower_bound(gv[x[i]].begin(), gv[x[i]].end(), high) - gv[x[i]].begin() - 1;
                ans = ans - max(0, id2 - id1);
                debug("now the answer is %lld\n", ans);
            } else {
                debug("calculate <%d,%d> previous answer = %lld\n", discx[x[i]-1], discy[y[i]-1], ans);
                int low = *prev(hasV.lower_bound(x[i])), high = *hasV.lower_bound(x[i]);
                ans = ans + max(prex[high - 1] - prex[low] - 1, 0);
                debug("first step ans --> %lld\n", ans);
                int id1 = upper_bound(gh[y[i]].begin(), gh[y[i]].end(), low) - gh[y[i]].begin();
                int id2 = lower_bound(gh[y[i]].begin(), gh[y[i]].end(), high) - gh[y[i]].begin() - 1;
                ans = ans - max(0, id2 - id1);
                debug("now the answer is %lld\n", ans);
            }
        }

        printf("%lld\n", ans / 2);
    }
    return 0;
}