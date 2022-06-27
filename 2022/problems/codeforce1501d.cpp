#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1000111
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

vector<pair<ll, ll>> bad;

pair<ll, ll> solve(ll x, ll sx, ll y, ll sy) {
    /*
        ans = x (mod sx)
        ans = y (mod sy)
    */
    vector<ll> m = {sx, sy}, r = {x % sx, y % sy};
    auto ret = make_pair(extented_crt(m, r), sx * sy / gcd(sx, sy));
    debug("r=[%lld, %lld], mod=[%lld,%lld], get <%lld,%lld>\n", r[0], r[1], m[0], m[1], ret.first, ret.second);
    return ret;
}

bool check(ll day, ll limit) {
    ll tol = 0;
    for (auto p : bad) {
        if (p.first <= day) {
            tol = tol + (day - p.first) / p.second + 1;
        }

        if (tol > limit) return false;
    }

    return true;
}

int a[MAX_SIZE], b[MAX_SIZE], pos[MAX_SIZE][2];
int N, M;
ll K;

int main() {
    int i;
    scanf("%d%d%lld", &N, &M, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        pos[a[i]][0] = i;
    }

    for (i = 1; i <= M; ++i) {
        scanf("%d", &b[i]);
        pos[b[i]][1] = i;
    }

    for (i = 1; i <= 2 * max(N, M); ++i) {
        if (pos[i][0] != 0 && pos[i][1] != 0) {
            auto rt = solve(pos[i][0], N, pos[i][1], M);
            if (rt.first == -1) continue;
            bad.push_back(rt);
        }
    }

    ll low = K, high = 3e18, ans = 3e18;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (check(mid, mid - K)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%lld\n", ans);
    return 0;
}