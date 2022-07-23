#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
#define BLOCK 450
#define MAX_LOG 19
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

int logs[MAX_SIZE];

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int a[MAX_SIZE];

struct ST {
    
    int table[MAX_LOG][MAX_SIZE];
    int n;
    int tp;

    int RMQ(int l, int r) {
        if (l > r) return 4 * MAX_SIZE * (tp ? 1 : -1);
        int len = r - l + 1;
        if (tp) {
            return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        } else {
            return max(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
        }
    }

    void build() {
        int i, j;
        for (i = 1; i <= n; i++) {
            table[0][i] = a[i];
        }
        
        for (i = 1; i < MAX_LOG; i++) {
            int prel = (1 << (i - 1));
            for (j = 1; j <= n; j++) {
                if (j + prel <= n) {
                    if (tp) {
                        table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
                    } else {
                        table[i][j] = max(table[i-1][j], table[i-1][j+prel]);
                    }
                } else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }
};

ST mn;
int N, M, Q;

int main() {
    precompute();
    scanf("%d%d", &N, &M);
    mn.tp = 1;
    mn.n = M;
    int i;
    for (i = 1; i <= M; ++i) {
        int v;
        scanf("%d", &v);
        a[i] = N - v;
    } 

    mn.build();

    scanf("%d", &Q);
    while (Q-- > 0) {
        int xs, ys, xf, yf, k;
        scanf("%d%d%d%d%d", &ys, &xs, &yf, &xf, &k);
        ys = N - ys + 1;
        yf = N - yf + 1;
        if (abs(xs - xf) % k != 0 || abs(ys - yf) % k != 0) {
            printf("NO\n");
        } else {
            ys = ys % k;
            if (ys == 0) ys = k;
            if (xs > xf) swap(xs, xf);
            if (mn.RMQ(xs, xf) >= ys) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    return 0;
}