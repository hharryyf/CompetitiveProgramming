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

ll X = 4;
ll lim = 2e9;

ll query(ll a, ll b) {
    bool flag = false;
    #ifdef D
        flag = true;
    #endif

    if (a > lim || b > lim) return -1;

    if (flag) {
        cout << "? " << a << " " << b << endl;
        cout << gcd(a + X, b + X) << endl; 
        return gcd(a + X, b + X);
    } else {
        cout << "? " << a << " " << b << endl;
        cin >> a;
        return a;
    }
}

vector<ll> m;
vector<ll> r;
ll shift = 1078282205ll;

void init() {
    m.clear();
    m.push_back(5);
    m.push_back(7);
    m.push_back(11);
    m.push_back(13);
    m.push_back(17);
    m.push_back(19);
    m.push_back(23);
    m.push_back(29);
    r = vector<ll>(8, 0);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        init();
        for (i = 1; i <= 29; ++i) {
            auto rt = query(i, i + shift);
            for (int j = 0 ; j < (int) m.size(); ++j) {
                if (rt % m[j] == 0) {
                    r[j] = (m[j] - i) % m[j] + m[j];
                }
            }
        }

        cout << "! " << extented_crt(m, r) << endl;
    }
    return 0;
}