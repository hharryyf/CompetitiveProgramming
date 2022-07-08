#define D
#define MAX_SIZE 5011
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

int pre[MAX_SIZE];
int mx[MAX_SIZE];
int N;

int query(int l, int r) {
    return pre[r] - pre[l-1];
}

void update(int l, int r) {
    int ans = query(l, r);
    mx[r - l + 1] = max(ans, mx[r - l + 1]);
    // debug("query[%d,%d] = %d update to %d\n", l, r, ans, mx[r-l+1]);
}

void calc() {
    int i;
    for (i = N - 1; i >= 0; --i) {
        mx[i] = max(mx[i], mx[i+1]);
    }
}

int ret[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        int x;
        scanf("%d%d", &N, &x);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &pre[i]);
            pre[i] += pre[i-1];
            mx[i] = pre[i];
        }

        mx[0] = 0;

        for (i = 1; i <= N; ++i) {
            for (j = i; j <= N; ++j) {
                update(i, j);
            }
        }

        calc();
        for (i = 0 ; i <= N; ++i) {
            ret[i] = i * x + mx[i];
            if (i > 0) {
                ret[i] = max(ret[i], ret[i-1]);
            } 

            printf("%d ", ret[i]);
        }


        printf("\n");
    }

    return 0;
}
