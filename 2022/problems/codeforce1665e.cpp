#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 262192
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
typedef long double ld;

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

int a[MAX_SIZE], N;
pair<int, int> tree[MAX_SIZE];

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].first = a[l];
        tree[index].second = l;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

pair<int, int> query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return make_pair((1 << 30) + (1 << 28), -1);
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return min(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void update(int pt, int l, int r, int index, int val) {
    if (pt < l || l > r || pt > r) return;
    if (l == r) {
        tree[index].first = val;
        return;
    }

    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }

    tree[index] = min(tree[LEFT], tree[RIGHT]);
}

int mn[33], cnt;

int main() {
    int i, j;
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        build(1, N, 1);
        
        int Q;
        scanf("%d", &Q);
        while (Q-- > 0) {
            int l, r;
            cnt = 0;
            scanf("%d%d", &l, &r);
            i = min(r - l + 1, 31);
            while (i > 0) {
                auto q = query(l, r, 1, N, 1);
                mn[++cnt] = q.second;
                update(q.second, 1, N, 1, (1 << 30) + (1 << 28));
                --i;
            }

            int ans = (1 << 30) + (1 << 28);

            for (i = 1; i <= cnt; ++i) {
                for (j = i + 1; j <= cnt; ++j) {
                    ans = min(ans, a[mn[i]] | a[mn[j]]);
                }
            }

            for (i = 1; i <= cnt; ++i) {
                update(mn[i], 1, N, 1, a[mn[i]]);
            }

            printf("%d\n", ans);
        }
    }
    return 0;
}