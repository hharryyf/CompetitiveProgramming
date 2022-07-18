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

ll pre[MAX_SIZE];
ll dp[MAX_SIZE][452];
int N;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%lld", &pre[i]);
            pre[i] += pre[i-1];
        }

        for (i = 1; i <= N + 1; ++i) {
            for (j = 1; j <= 450; ++j) {
                dp[i][j] = -infll;
            }
        }

        for (i = 1; i <= N; ++i) {
            dp[i][1] = pre[i] - pre[i-1];
        }

        for (i = N - 1; i >= 1; --i) {
            dp[i][1] = max(dp[i+1][1], dp[i][1]);
        }

        for (j = 2; j <= 450; ++j) {
            for (i = N; i >= 1; --i) {
                if (i < N) {
                    dp[i][j] = max(dp[i+1][j], dp[i][j]);
                }

                if (i + j <= N && pre[i + j - 1] - pre[i - 1] < dp[i+j][j-1]) {
                    dp[i][j] = max(dp[i][j], pre[i + j - 1] - pre[i - 1]);
                }
            }
        }

        for (i = 450; i >= 1; --i) {
            if (dp[1][i] > 0) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}