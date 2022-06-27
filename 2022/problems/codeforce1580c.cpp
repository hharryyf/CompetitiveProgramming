#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
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

const ll mod = 998244353;

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

pair<int, int> model[MAX_SIZE];
int lst[MAX_SIZE];
int tol[BLOCK][BLOCK];
int large[MAX_SIZE];
int delta[MAX_SIZE];

int main() {
    int N, M, i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &model[i].first, &model[i].second);
    }

    for (i = 1; i <= M; ++i) {
        int op, idx, dt = -1;
        scanf("%d%d", &op, &idx);
        if (op == 1) {
            dt = 1;
            lst[idx] = i;
        }

        int sz = model[idx].first + model[idx].second;
        if (sz < BLOCK) {
            debug("operation is %d modify from %d to %d\n", op, model[idx].first, sz - 1);
            for (j = model[idx].first; j < sz; ++j) {
                tol[sz][(lst[idx] + j) % sz] += dt;
                debug("add to block %d mod %d value %d\n", sz, (lst[idx] + j) % sz, dt); 
            }
        } else {
            for (j = lst[idx]; j <= M; j = j + sz) {
                if (j + model[idx].first <= M) {
                    debug("add range [%d,%d] value %d\n", j + model[idx].first, j + sz - 1, dt);

                    if (op == 1) {
                        large[j + model[idx].first] += 1;
                        if (j + sz <= M) {
                            large[j + sz] -= 1;
                        }    
                    } else {
                        // delete the range [j + model[idx].first, j + sz - 1]
                        // if i is before just remove
                        if (i < j + model[idx].first) {
                            large[j + model[idx].first] -= 1;
                            if (j + sz <= M) {
                                large[j + sz] += 1;
                            }   
                        } else if (i <= j + sz - 1 && i >= j + model[idx].first) {
                            large[i] -= 1;
                            if (j + sz <= M) {
                                large[j + sz] += 1;
                            }
                        }
                    }
                }
            }
        }

        for (j = 1; j < BLOCK; ++j) {
            delta[i] += tol[j][i % j];
        }
    }

    for (i = 1; i <= M; ++i) {
        large[i] += large[i-1];
        printf("%d\n", delta[i] + large[i]);
    }
    return 0;
}