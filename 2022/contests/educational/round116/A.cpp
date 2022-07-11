#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 100011
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

char s[111];

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s + 1);
        int N = strlen(s + 1);
        int ab = 0, ba = 0;
        for (i = 2; i <= N; ++i) {
            if (s[i] == 'b' && s[i-1] == 'a') {
                ab++;
            } else if (s[i] == 'a' && s[i-1] == 'b') {
                ba++;
            }
        }

        if (ab == ba) {
            printf("%s\n", s + 1);
        } else {
            for (i = 1; i <= N; ++i) {
                if (s[i] == 'a') {
                    s[i] = 'b';
                } else {
                    s[i] = 'a';
                }

                ab = 0, ba = 0;
                for (int j = 2; j <= N; ++j) {
                    if (s[j] == 'b' && s[j-1] == 'a') {
                        ab++;
                    } else if (s[j] == 'a' && s[j-1] == 'b') {
                        ba++;
                    }
                }
                if (ab == ba) {
                    printf("%s\n", s + 1);
                    break;
                }
                if (s[i] == 'a') {
                    s[i] = 'b';
                } else {
                    s[i] = 'a';
                }
            }
        }
    }
    return 0;
}