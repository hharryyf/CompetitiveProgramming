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

char s[MAX_SIZE];
char t[MAX_SIZE];

int main() {
    int T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, l = 0, r = 0;
        scanf("%s", s + 1);
        N = strlen(s + 1);
        for (i = 1; i <= N; ++i) {
            if (s[i] == '(') l++;
            if (s[i] == ')') r++;
        }
        t[N + 1] = '\0';

        int lb = N / 2 - l, rb = N / 2 - r;
        if (lb == 0 || rb == 0) {
            printf("YES\n");
            continue;
        }

        int tlb = lb, trb = rb;

        for (i = 1; i <= N; ++i) t[i] = s[i];

        for (i = 1; i <= N && tlb > 0; ++i) {
            if (s[i] == '?') {
                t[i] = '(';
                tlb--;
            }
        }

        for (i = 1; i <= N && trb > 0; ++i) {
            if (s[i] == '?' && t[i] == '?') {
                t[i] = ')';
                trb--;
            }
        }

        int lstl = 0, lstr = 0;
        for (i = 1; i <= N; ++i) {
            if (s[i] == '?' && t[i] == '(') {
                lstl = i;
            }
        }

        for (i = N; i >= 1; --i) {
            if (s[i] == '?' && t[i] == ')') {
                lstr = i;
            }
        }

        swap(t[lstl], t[lstr]);
        //printf("%s\n", s + 1);
        //printf("%s\n", t + 1);

        int sm = 0;
        bool ok = true;
        for (i = 1; i <= N; ++i) {
            if (t[i] == '(') sm++;
            else {
                sm--;
            }

            if (sm < 0) {
                ok = false;
                break;
            }
        }

        if (ok) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}