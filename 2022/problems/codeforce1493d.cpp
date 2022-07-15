#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 201011
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

const ll mod = 1000000007;

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

vector<int> prime[MAX_SIZE];
int visited[MAX_SIZE];

struct frequency {
    map<int, int> posTocnt;
    multiset<int> cnt;
    int N;
    int query() {
        if ((int) cnt.size() < N) return 0;
        return *cnt.begin();
    }
 
    void update(int x, int f) {
        if (posTocnt.find(x) == posTocnt.end()) {
            posTocnt[x] = f;
            cnt.insert(f);
        } else {
            int c = posTocnt[x];
            cnt.erase(cnt.find(c));
            posTocnt[x] = f + c;
            cnt.insert(f + c);
        }
    }
};

frequency f[MAX_SIZE];
ll ans = 1;

int main() {
    int i, j;
    for (i = 2; i < MAX_SIZE; ++i) {
        if (!visited[i]) {
            for (j = 1; j * i < MAX_SIZE; ++j) {
                visited[i * j] = 1;
                prime[i * j].push_back(i);
            }
        }
    }

    int N, Q;
    scanf("%d%d", &N, &Q);
    for (i = 2; i < MAX_SIZE; ++i) {
        if (visited[i]) f[i].N = N;
    }

    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        int pp = v;
        for (auto p : prime[v]) {
            int c = 0;
            while (pp % p == 0) {
                pp /= p;
                c++;
            }
            int q1 = f[p].query();
            f[p].update(i, c);
            int q2 = f[p].query();
            ans = mul(ans, qpow(p, q2 - q1));
        }
    }

    while (Q-- > 0) {
        int x, v;
        scanf("%d%d", &x, &v);
        int pp = v;
        for (auto p : prime[v]) {
            int c = 0;
            while (pp % p == 0) {
                pp /= p;
                c++;
            }
            int q1 = f[p].query();
            f[p].update(x, c);
            int q2 = f[p].query();
            ans = mul(ans, qpow(p, q2 - q1));
        }

        printf("%lld\n", ans);
    }
    return 0;
}