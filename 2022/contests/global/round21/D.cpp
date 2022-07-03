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

int logs[MAX_SIZE];

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int a[MAX_SIZE];

struct ST {
    
    int table[19][MAX_SIZE];
    int n;
    int tp;

    int RMQ(int l, int r) {
        if (l > r) return 4 * MAX_SIZE * (tp ? 1 : -1);
        int len = r - l + 1;
        if (tp) {
            return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        } else {
            return max(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        }
    }

    void build() {
        int i, j;
        for (i = 1; i <= n; i++) {
            table[0][i] = a[i];
        }
        
        for (i = 1; i <= 18; i++) {
            int prel = (1 << (i - 1));
            for (j = 1; j <= n; j++) {
                if (j + prel <= n) {
                    if (tp) {
                        table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
                    } else {
                        table[i][j] = max(table[i-1][j], table[i-1][j+prel]);
                    }
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }
};

ST mn, mx;
int N;
int small[MAX_SIZE], big[MAX_SIZE];

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            small[i] = big[i] = 0;
        } 
        
        vector<int> pos;
        for (i = N; i >= 1; --i) {
            if (pos.empty()) {
                pos.push_back(i);
            } else {
                while (!pos.empty() && a[pos.back()] < a[i]) {
                    pos.pop_back();
                } 

                if (!pos.empty()) {
                    big[i] = pos.back();
                } 
                pos.push_back(i);
            }
        }

        pos.clear();
        for (i = N; i >= 1; --i) {
            if (pos.empty()) {
                pos.push_back(i);
            } else {
                while (!pos.empty() && a[pos.back()] > a[i]) {
                    pos.pop_back();
                } 

                if (!pos.empty()) {
                    small[i] = pos.back();
                } 
                pos.push_back(i);
            }
        }
        mn.tp = 1;
        mx.tp = 0;
        mn.n = mx.n = N;
        mn.build();
        mx.build();


        int curr = 1, ans = 0;
        while (curr < N) {
            if (a[curr] < a[curr + 1]) {
                int idx = curr;
                while (big[idx] != 0 && mn.RMQ(curr, big[idx]) == a[curr]) {
                    debug("move from big %d -> %d\n", idx, big[idx]);
                    idx = big[idx];
                }

                curr = idx;
            } else {
                int idx = curr;
                while (small[idx] != 0 && mx.RMQ(curr, small[idx]) == a[curr]) {
                    debug("move from small %d -> %d\n", idx, small[idx]);
                    idx = small[idx];
                    
                }

                curr = idx;
            }

            ans++;
        }

        printf("%d\n", ans);
    }
    return 0;
}