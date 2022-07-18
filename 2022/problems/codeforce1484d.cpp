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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef long double ld;

const ll mod = 998244353;
const int infint = 1030000000;
const ll infll = 1e18 + 17;

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

int a[MAX_SIZE];

int nxt[MAX_SIZE];
int pre[MAX_SIZE];
set<pair<int, int>> critical;
        
pair<int, int> find_next(int pos) {
    if (critical.empty()) return make_pair(-1, -1);
    auto it = critical.lower_bound(make_pair(pos, -1));
    if (it != critical.end()) {
        return *it;
    }

    return *critical.begin();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        critical.clear();
        vector<int> ans;
        int i, N;
        scanf("%d", &N);
        for (i = 0; i < N; ++i) {
            nxt[i] = (i + 1) % N;
            pre[(i + 1) % N] = i;
            scanf("%d", &a[i]);
        }

        for (i = 0 ; i < N; ++i) {
            if (gcd(a[i], a[(i+1) % N]) == 1) {
                critical.insert(make_pair(i, (i + 1) % N));
            }
        }

        int idx = 0;
        while (true) {
            for (auto iter : pre) {
                debug("pre[%d] = %d ; ", iter.first, iter.second);
            }
            debug("\n");
            for (auto iter : nxt) {
                debug("nxt[%d] = %d ; ", iter.first, iter.second);
            }
            debug("\n");
            pair<int, int> it = find_next(idx);
            if (it.first == -1) break;
            if (nxt[it.second] != -1 && pre[it.second] != -1
               && pre[it.first] != -1 && nxt[it.first] != -1) {
                ans.push_back(it.second);
            }
            critical.erase(it);
            int pr = pre[it.second];
            int ne = nxt[it.second];
            if (critical.find({it.second, ne}) != critical.end()) critical.erase(make_pair(it.second, ne));
            pre[ne] = pr;
            nxt[pr] = ne;
            pre[it.second] = -1;
            nxt[it.second] = -1;
            debug("delete index %d\n", it.second);
            if (nxt[pr] != -1 && nxt[ne] != -1) {
                if (gcd(a[pr], a[ne]) == 1) {
                    critical.insert(make_pair(pr, ne));
                    debug("we found index %d and %d has gcd 1\n", pr, ne);
                }
            }
            idx = it.second + 1;
        }

        printf("%d", (int) ans.size());
        for (auto v : ans) {
            printf(" %d", v + 1);
        }
        printf("\n");

    }
    return 0;
}