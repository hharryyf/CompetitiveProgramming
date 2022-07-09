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
 
ll fac[MAX_SIZE], ifac[MAX_SIZE];
 
void init_1() {
    int i;
    fac[0] = ifac[0] = 1;
    for (i = 1 ; i < MAX_SIZE; ++i) {
        fac[i] = mul(fac[i-1], i);
        ifac[i] = mul(ifac[i-1], qpow(i, mod - 2));
    }
}
 
ll C(int n, int k) {
    if (n < k) return 0;
    return mul(fac[n], mul(ifac[n-k], ifac[k]));
}

int visited[MAX_SIZE];
int ans[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j;
        scanf("%d", &N);
        vector<int> ret;
        for (i = 1; i <= N; ++i) visited[i] = 0;
        for (i = 1; i <= N; ++i) {
            if (!visited[i]) {
                j = i;
                while (j <= N && !visited[j]) {
                    ret.push_back(j);
                    visited[j] = 1;
                    j = j * 2;
                }
            }
        }

        printf("2\n");
        for (auto v : ret) {
            printf("%d ", v);
        }

        printf("\n");
    }
    return 0;
}