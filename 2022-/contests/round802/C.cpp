// #define D
#define MAX_SIZE 524312
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <bits/stdc++.h>
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
ll a[MAX_SIZE];

struct BIT {
    ll tree[MAX_SIZE];
    int shift(int x) {
        return x & (-x);
    }

    void inc(int pos, ll val) {
        while (pos <= N) {
            tree[pos] += val;
            pos += shift(pos);
        }
    }

    void update(int l, int r, ll val) {
        inc(l, val);
        inc(r + 1, -val);
    }

    ll ask(int pos) {
        ll ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos -= shift(pos);
        }

        return ret;
    }
};

BIT tree;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        ll ans = 0;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) scanf("%lld", &a[i]);
        for (i = 1; i <= N; ++i) {
            tree.tree[i] = 0;
        }

        for (i = 1; i <= N; ++i) {
            tree.update(i, i, a[i]);
        }

        for (i = 2; i <= N; ++i) {
            ll x = tree.ask(i - 1);
            ll y = tree.ask(i);
            if (x > y) {
                tree.update(1, i - 1, y - x);
                ans += x - y;
            } else if (x < y) {
                tree.update(i, N, x - y);
                ans += y - x;
            }
        }

        ans += llabs(tree.ask(1));

        printf("%lld\n", ans);
    }
    return 0;
}