#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 1048597
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

struct segt {
    int cnt, status;
};

char s[MAX_SIZE];
map<pair<int, int>, int> idx;
pair<int, int> game[MAX_SIZE];
segt tree[MAX_SIZE];

segt pullup(segt t1, segt t2, int status) {
    segt ret;
    ret.status = status;
    if (ret.status == 0) {
        ret.cnt = t1.cnt;
    } else if (ret.status == 1) {
        ret.cnt = t2.cnt;
    } else {
        ret.cnt = t1.cnt + t2.cnt;
    }

    return ret;
}


void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].cnt = 1;
        tree[index].status = -1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    char ch = s[idx[{l, r}]];
    if (ch == '0') {
        tree[index].status = 0;
    } else if (ch == '1') {
        tree[index].status = 1;
    } else {
        tree[index].status = -1;
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT], tree[index].status);
}

void update(int start, int end, int l, int r, int index, int status) {
    if (start > end || l > r || start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].status = status;
        tree[index] = pullup(tree[LEFT], tree[RIGHT], status);
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, status);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT,status);
    } else {
        update(start, end, l, MID, LEFT, status);
        update(start, end, MID + 1, r, RIGHT,status);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT], tree[index].status);
}

char tp[4];

int main() {
    int i, j, M, N, cnt = 1;
    scanf("%d", &M);
    N = 1 << M;
    scanf("%s", s + 1);
    for (i = 1; i <= M; ++i) {
        for (j = 1; j <= N; j = j + (1 << i)) {
            game[cnt].first = j;
            game[cnt].second = j + (1 << i) - 1;
            idx[{game[cnt].first, game[cnt].second}] = cnt;
            cnt++; 
        }
    }

    for (i = 1; i < 1 << M; ++i) {
        debug("game[%d]: (%d, %d)\n", i, game[i].first, game[i].second);
    }

    build(1, N, 1);
    int Q;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int p;
        scanf("%d%s", &p, tp);
        if (tp[0] == '0') {
            update(game[p].first, game[p].second, 1, N, 1, 0);
        } else if (tp[0] == '1') {
            update(game[p].first, game[p].second, 1, N, 1, 1);
        } else {
            update(game[p].first, game[p].second, 1, N, 1, -1);
        }
        printf("%d\n", tree[1].cnt);
    }
    return 0;
}