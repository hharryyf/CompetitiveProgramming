#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 111
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
#include <bitset>
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

char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        multiset<int> st;
        scanf("%s", s + 1);
        int i, N = strlen(s + 1);
        for (i = 1; i <= N; ++i) {
            st.insert(s[i] - '0');
        }

        if (st.find(0) != st.end()) {
            st.erase(st.find(0));
        } else {
            printf("cyan\n");
            continue;
        }

        if (st.find(0) != st.end() || st.find(2) != st.end() || st.find(6) != st.end() || st.find(4) != st.end() ||st.find(8) != st.end()) {
            int sm = 0;
            for (auto v : st) {
                sm += v;
            }

            if (sm % 3 == 0) {
                printf("red\n");
            } else {
                printf("cyan\n");
            }
        } else {
            printf("cyan\n");
        }
    }
    return 0;
}