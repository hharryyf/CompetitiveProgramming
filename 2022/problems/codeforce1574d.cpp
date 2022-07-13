#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 11
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
set<vector<int>> ban;
vector<int> ans;
int sm = 0;
int res;
int N, M;
vector<int> current;

bool check(vector<int> &curr) {
    return ban.find(curr) == ban.end();
}

void solve(int idx) {
    int i;
    for (i = (int) g[idx].size() - 1; i >= 0; --i) {
        sm += g[idx][i];
        current.push_back(i);
        if (idx == N - 1) {
            if (check(current)) {
                if (sm > res) {
                    res = sm;
                    ans = current;
                    
                } 

                current.pop_back();
                sm -= g[idx][i];
                break;
            }
            current.pop_back();
            sm -= g[idx][i];    
        } else {
            bool ok = false;
            for (int j = idx + 1; j < N; ++j) {
                current.push_back((int) g[j].size() - 1);
                sm += g[j].back();
            }

            if (check(current)) {
                if (sm > res) {
                    res = sm;
                    ans = current;
                }

                ok = true;
            }

            for (int j = N - 1; j >= idx + 1; --j) {
                sm -= g[j][current.back()];
                current.pop_back();
            }

            if (!ok) {
                solve(idx + 1);
                sm -= g[idx][i];
                current.pop_back();
            } else {
                sm -= g[idx][i];
                current.pop_back();
                break;
            }
        }
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        int ci;
        scanf("%d", &ci);
        while (ci > 0) {
            int v;
            scanf("%d", &v);
            g[i].push_back(v);
            --ci;
        }
    }

    scanf("%d", &M);
    for (i = 1; i <= M; ++i) {
        int j;
        vector<int> curr(N);
        for (j = 0; j < N; ++j) {
            scanf("%d", &curr[j]);
            curr[j]--;
        }

        ban.insert(curr);
    }

    solve(0);

    for (auto v : ans) {
        printf("%d ", v + 1);
    }
    printf("\n");

    return 0;
}