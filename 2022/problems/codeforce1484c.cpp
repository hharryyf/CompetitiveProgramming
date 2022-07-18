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

vector<int> g[MAX_SIZE];
int N, M;
int cnt[MAX_SIZE];
int ans[MAX_SIZE];
vector<int> occ[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        int i;
        for (i = 1; i <= N; ++i) {
            cnt[i] = 0;
            occ[i].clear();
        }
        for (i = 1; i <= M; ++i) {
            ans[i] = 0;
            g[i].clear();
            int k;
            scanf("%d", &k);
            while (k-- > 0) {
                int v;
                scanf("%d", &v);
                g[i].push_back(v);
                occ[v].push_back(i);
            }
        }
        
        bool ok = true;
        int lim = (M + 1) / 2;
        for (i = 1; i <= M; ++i) {
            if ((int) g[i].size() == 1) {
                ans[i] = g[i].front();
                cnt[ans[i]]++;
            }
            
            if (cnt[ans[i]] > lim) {
                ok = false;
                break;
            }
        }
        
        if (!ok) {
            printf("NO\n");
            continue;
        }
        
        printf("YES\n");
        int mx = 1;
        for (i = 1; i <= N; ++i) {
            if ((int) g[i].size() > lim && cnt[i] > cnt[mx]) mx = i;
        }
        
        
        for (auto id : occ[mx]) {
            if (!ans[id] && cnt[mx] < lim) {
                ans[id] = mx;
                cnt[mx]++;
            }
        }
        
        for (i = 1; i <= M; ++i) {
            if (!ans[i]) {
                for (auto v : g[i]) {
                    if (cnt[v] < lim) {
                        cnt[v]++;
                        ans[i] = v;
                        break;
                    }
                }
            }
        }
        
        for (i = 1; i <= M; ++i) {
            printf("%d ", ans[i]);
        }
        printf("\n");
    }
    
    return 0;
}