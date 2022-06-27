#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 211
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

int query(string &ss) {
    cout << ss << endl;
    int x;
    cin >> x;
    return x;
}

string s;

int main() {
    int i, qa = 0, qb = 0;
    // qa + qb + l = 300
    // qb + l = da
    // qa + l = db
    s.clear();
    for (i = 1; i <= 300; ++i) {
        s += 'a';
    }

    int d = query(s);
    qa = 300 - d;
    
    s.clear();

    for (i = 1; i <= 300; ++i) {
        s += 'b';
    }

    d = query(s);
    qb = 300 - d;

    s.clear();
    for (i = 1; i <= qa + qb; ++i) {
        s += 'a';
    }

    d = qb;
    for (i = 0; i < qa + qb - 1; ++i) {
        if (s[i] == 'a') {
            s[i] = 'b';
        } else {
            s[i] = 'a';
        }

        int curr = query(s);
        if (curr <= d) {
            d = curr;
        } else {
            if (s[i] == 'a') {
                s[i] = 'b';
            } else {
                s[i] = 'a';
            }
        }
    }

    int ca = 0, cb = 0;
    for (i = 0 ; i < qa + qb - 1; ++i) {
        if (s[i] == 'a') ca++;
        else {
            cb++;
        }
    }

    if (qa != ca) {
        s[qa + qb - 1] = 'a';
    } else {
        s[qa + qb - 1] = 'b';
    }

    cout << s << endl;
    return 0;
}