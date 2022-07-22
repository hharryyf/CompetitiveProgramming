#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 200011
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

int dp[MAX_SIZE][21];
int mn[MAX_SIZE][21];
int a[MAX_SIZE];
int lst[10000011];
vector<int> prime;
int tol[10000011];

void init() {
    int i;
    for (i = 2; i <= 10000000; ++i) {
        if (lst[i] == 0) {
            lst[i] = i;
            prime.push_back(i);
        }

        for (auto x : prime) {
            if (x > lst[i] || x * i > 10000000) break;
            lst[i * x] = x;
        }
    }
}

int main() {
    int T;
    init();
    scanf("%d", &T);
    while (T-- > 0) {
        int N, K, i, j, k;
        scanf("%d%d", &N, &K);
        for (i = 0; i < N; ++i) {
            int v;
            scanf("%d", &v);
            a[i] = 1;
            int cnt = 0, l = 0;
            while (v > 1) {
                int p = lst[v];
                if (l == p) {
                    ++cnt;
                } else {
                    if (cnt % 2 == 1) {
                        a[i] *= l;
                    }
                    l = p;
                    cnt = 1;
                }

                v /= p;
            }

            if (cnt % 2 == 1) a[i] *= l;
        }

        for (i = 0 ; i <= N; ++i) {
            for (j = 0; j <= K; ++j) {
                mn[i][j] = 0;
                dp[i][j] = infint;
            }
        }

        for (j = 0 ; j <= K; ++j) {
            int l = N, curr = 0;
            for (i = N - 1; i >= 0; --i) {
                while (l - 1 >= 0 && curr + (tol[a[l-1]] > 0) <= j) {
                    l--;
                    curr = curr + (tol[a[l]] > 0);
                    tol[a[l]]++;
                }

                mn[i][j] = l;
                if (tol[a[i]] > 1) curr--;
                tol[a[i]]--;
            }
        }

        for (i = 0 ; i <= K; ++i) dp[0][i] = 0;
        for (i = 1; i <= N; ++i) {
            for (j = 0 ; j <= K; ++j) {
                if (j > 0) dp[i][j] = dp[i][j-1];
                for (k = 0; k <= j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[mn[i-1][k]][j-k] + 1);
                }
            }
        }

        int ans = infint;

        for (i = 0; i <= K; ++i) {
            ans = min(ans, dp[N][i]);
        }

        printf("%d\n", ans);
    }
    return 0;
}