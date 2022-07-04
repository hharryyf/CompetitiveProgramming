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

int N;
int p[MAX_SIZE];
char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        int i;
        for (i = 1; i <= N; ++i) scanf("%d", &p[i]);
        scanf("%s", s + 1);
        vector<pair<int, int>> low, high;
        for (i = 1; i <= N; ++i) {
            if (s[i] == '0') {
                low.emplace_back(p[i], i);
            } else {
                high.emplace_back(p[i], i);
            }
        }

        sort(low.begin(), low.end());
        sort(high.begin(), high.end());
        int cnt = 1;
        for (auto pp : low) {
            p[pp.second] = cnt++;
        }

        for (auto pp : high) {
            p[pp.second] = cnt++;
        }

        for (i = 1; i <= N; ++i) {
            printf("%d ", p[i]);
        }
        printf("\n");
    }
    return 0;   
}