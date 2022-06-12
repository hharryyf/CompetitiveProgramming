#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1011
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

int N, cnt;
vector<int> g[MAX_SIZE];
int id[MAX_SIZE], rid[MAX_SIZE], parent[MAX_SIZE];

int query(int x) {
    if (x == 1) return -1;
    cout << "? " << x;
    for (int i = 1; i <= x; ++i) {
        cout << " " << rid[i];
    }
    cout << endl;
    cin >> x;
    return x;
}

void dfs(int v, int pre) {
    id[v] = ++cnt;
    rid[id[v]] = v;
    parent[v] = pre;
    for (auto nv : g[v]) {
        if (nv != pre) {
            dfs(nv, v);
        }
    }
}

int main() {
    cin >> N;
    int low = 1, high = N, ans = 0;
    for (int i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    int target = query(N);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (query(mid) == target) {
            high = mid - 1;
            ans = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << "! " << rid[ans] << " " << parent[rid[ans]] << endl;
    return 0;
}