#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 603
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

/*
    dist(u, i) + w(i, j) + dist(j, v) <= L(u, v)
    w(i, j) + dist(j, v) <= L(u, v) - dist(u, i) = P(v, i) for some u
    Hence, we iterate through i, j, v
    see if there exists dist(i, j) + dist(j, v) <= P(v, i)
*/

ll w[MAX_SIZE][MAX_SIZE], dist[MAX_SIZE][MAX_SIZE], p[MAX_SIZE][MAX_SIZE], lim[MAX_SIZE][MAX_SIZE];

int main() {
    int N, M, Q;
    int i, j, k;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        int u, v;
        ll ww;
        scanf("%d%d%lld", &u, &v, &ww);
        w[u][v] = w[v][u] = ww;
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            lim[i][j] = infll;
            p[i][j] = -infll;
        }
    }

    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        int u, v;
        ll l;
        scanf("%d%d%lld", &u, &v, &l);
        lim[u][v] = lim[v][u] =min(lim[u][v], l);
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (i != j) {
                dist[i][j] = infll;
            }

            if (w[i][j]) {
                dist[i][j] = w[i][j];
            }
        }
    }

    for (k = 1; k <= N; ++k) {
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            for (k = 1; k <= N; ++k) {
                if (lim[i][j] < infll) {
                    p[j][k] = max(lim[i][j] - dist[i][k], p[j][k]);
                }
            }
        }
    }

    int ans = 0;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            for (k = 1; k <= N; ++k) {
                if (w[i][j] && dist[j][k] < infll) {
                    if (w[i][j] + dist[j][k] <= p[k][i]) {
                        ans++;
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", ans / 2);
    return 0;
}