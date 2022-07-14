#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 500011
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

struct dup {
    map<pair<int, int>, char> st;
    int cnt = 0;

    void add(int x, int y, char ch) {
        st[make_pair(x, y)] = ch;
        if (st.find(make_pair(y, x)) != st.end()) {
            if (st[make_pair(y, x)] == ch) cnt++;
        }
    }

    void del(int x, int y) {
        auto ch = st[make_pair(x, y)];
        if (st.find(make_pair(y, x)) != st.end()) {
            if (st[make_pair(y, x)] == ch) cnt--;
        }

        st.erase(make_pair(x, y));
    }

    bool hasdup() {
        return cnt > 0;
    }
};

struct odd {
    set<pair<int, int>> st;
    int ok = 0;
    void update(int x, int y) {
        if (st.find(make_pair(x, y)) != st.end()) {
            st.erase(make_pair(x, y));
            if (st.find(make_pair(y, x)) != st.end()) {
                ok--;
            }
        } else {
            if (st.find(make_pair(y, x)) != st.end()) {
                ok++;
            }

            st.insert(make_pair(x, y));
        }
    }

    bool canodd() {
        return ok > 0;
    }
};

dup d;
odd o;
char s[4];
char ch[4];

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    while (M-- > 0) {
        int u, v;
        scanf("%s", s);
        if (s[0] == '+') {
            scanf("%d%d%s", &u, &v, ch);
            d.add(u, v, ch[0]);
            o.update(u, v);
        } else if (s[0] == '-') {
            scanf("%d%d", &u, &v);
            d.del(u, v);
            o.update(u, v);
        } else {
            scanf("%d", &u);
            if (d.hasdup()) {
                printf("YES\n");
                continue;
            }

            if (u % 2 == 1 && o.canodd()) {
                printf("YES\n");
                continue;
            }

            printf("NO\n");
        }
    }   
    return 0;
}