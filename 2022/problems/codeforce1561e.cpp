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


int a[MAX_SIZE], pos[MAX_SIZE];
int N;
// reverse the sequence of length v
void update(int v) {
    int i;   
    for (i = 1; i <= v / 2; ++i) {
        swap(a[i], a[v - i + 1]);
    }

    for (i = 1; i <= v; ++i) {
        pos[a[i]] = i;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            pos[a[i]] = i;
        }

        bool ok = true;
        for (i = 1; i <= N; ++i) {
            if ((i % 2) != (a[i] % 2)) ok = false;
        }

        if (!ok) {
            printf("-1\n");
            continue;
        }
        
        
    /*
        1 6 5 2 7 4 3 8 9
        7 2 5 6 1 4 3 8 9 <-- put the odd number 7 in the first place
        5 2 7 6 1 4 3 8 9 <-- put the odd number 7 just 1 place in front of the even number 6
        1 6 7 2 5 4 3 8 9 <-- reverse the sequence just 1 place after the number 6
        7 6 1 2 5 4 3 8 9 <-- reverse the sequence end up at 7
        3 4 5 2 1 6 7 8 9 <-- reverse the length 7 sequence
    */
        vector<int> op;
        for (i = N; i > 1; i = i - 2) {
            op.push_back(pos[i]);
            update(pos[i]);
            op.push_back(pos[i-1] - 1);
            update(pos[i-1] - 1);
            op.push_back(pos[i-1] + 1);
            update(pos[i-1] + 1);
            op.push_back(pos[i]);
            update(pos[i]);
            op.push_back(i);
            update(i);
        }

        printf("%d\n", (int) op.size());
        for (auto v : op) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}