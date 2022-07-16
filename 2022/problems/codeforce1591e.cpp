#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1048597
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

ll ex_euclidian(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = ex_euclidian(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll extented_crt(vector<ll> m , vector<ll> r){
    int n = m.size();
    ll MM = m[0] , R = r[0] , x , y , d;
    for(int i = 1; i < n; ++i){
        d = ex_euclidian(MM , m[i] , x , y);
        if((r[i] - R) % d)return -1;
        x = (r[i] - R) / d * x % (m[i] / d);
        R += x * MM;
        MM = MM / d * m[i];
        R %= MM;
    }
    return R > 0 ? R : R + MM;
}


int tree[MAX_SIZE << 1];
void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index] = 0;
        return;
    }
 
    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = tree[LEFT] + tree[RIGHT];
}
 
void change(int pt, int l, int r, int index, int val) {
    if (l > r || pt < l || pt > r) return;
    if (pt == l && l == r) {
        tree[index] += val;
        return;
    }
 
    if (pt <= MID) {
        change(pt, l, MID, LEFT, val);
    } else {
        change(pt, MID + 1, r, RIGHT, val);
    }
 
    tree[index] = tree[LEFT] + tree[RIGHT];
}
 
int extractk(int l, int r, int index, int k) {
    if (l > r || k <= 0) return -1;
    if (tree[index] < k) return -1;

    if (l == r) {
        return l;
    }
 
    if (tree[LEFT] >= k) {
        return extractk(l, MID, LEFT, k);
    } 

    return extractk(MID + 1, r, RIGHT, k - tree[LEFT]);
    
}

int query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return query(start, end, l, MID, LEFT) + query(start, end, MID + 1, r, RIGHT);
}

// the range tree stores how many numbers occur for each frequency

vector<int> g[MAX_SIZE];
// (id, l, k)
vector<array<int, 3>> q[MAX_SIZE];
// all numbers with frequency i
set<int> freq[MAX_SIZE];
// cnt[i] occurence of the ith number
int cnt[MAX_SIZE];
int a[MAX_SIZE];
int ans[MAX_SIZE];
int N, Q;

// increment the frequency of v by val
void inc(int v, int val) {
    int f = cnt[v];
    // debug("remove %d from frequency %d\n", v, f);
    if (f != 0) {
        freq[f].erase(v);
    }
    // debug("insert %d to frequency %d\n", v, f + val);
    if (f + val != 0) {
        freq[f + val].insert(v);
    }
    change(cnt[v], 1, N, 1, -1);
    cnt[v] += val;
    change(cnt[v], 1, N, 1, 1);
}

void dfs(int v) {
    inc(a[v], 1);
    // debug("solve for %d\n", v);
    for (auto qs : q[v]) {
        int id = qs[0], l = qs[1], k = qs[2];
        int tol = query(1, l - 1, 1, N, 1);
        if (tol + k > tree[1]) {
            ans[id] = -1;
        } else {
            int f = extractk(1, N, 1, tol + k);
            if (f == -1) {
                ans[id] = -1;
            } else {
                ans[id] = *freq[f].begin();
            }
        }
    }

    for (auto nv : g[v]) {
        dfs(nv);
    }

    inc(a[v], -1);
}

void init() {
    int i;
    for (i = 1; i <= N; ++i) {
        g[i].clear();
        q[i].clear();
        freq[i].clear();
        cnt[i] = 0;
    }

    build(1, N, 1);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &Q);
        init();
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
        }

        for (i = 2; i <= N; ++i) {
            int p;
            scanf("%d", &p);
            g[p].push_back(i);
        }

        for (i = 1; i <= Q; ++i) {
            int v, l, k;
            scanf("%d%d%d", &v, &l, &k);
            q[v].push_back({i, l, k});
        }

        dfs(1);

        for (i = 1; i <= Q; ++i) {
            printf("%d ", ans[i]);
        }

        printf("\n");
    }
    return 0;
}