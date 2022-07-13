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

char s[MAX_SIZE];
int N;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s + 1);
        int N = strlen(s + 1);
        int i;
        bool hassol = false;
        for (i = N; i >= 2; --i) {
            if ((s[i] - '0') + (s[i-1] - '0') >= 10) {
                int dt = (s[i] - '0') + (s[i-1] - '0');
                s[i-1] = dt / 10 + '0';
                s[i] = dt % 10 + '0';
                hassol = true;
                break;
            }
        }

        if (hassol) {
            printf("%s\n", s + 1);
        } else {
            
            printf("%d", (s[1] - '0') + (s[2] - '0'));
            for (int j = 3; j <= N; ++j) {
                printf("%c", s[j]);
            }
            printf("\n");
        }
    }
    return 0;
}