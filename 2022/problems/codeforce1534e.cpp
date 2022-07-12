#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
#define MAX_SIZE 511
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

int N, K;
int visited[MAX_SIZE];
int pre[MAX_SIZE];
int dist[MAX_SIZE];
/*
    states (x, y) such that the bitmask has x 0s and y 1s.
    x + y = N
    we want to calculate the shortest distance from (N, 0) to (0, N)
*/

const int inf = 100000000;

vector<int> BFS() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        dist[i] = inf;
        pre[i] = -1;
        visited[i] = 0;
    }

    vector<int> path;
    queue<int> q;
    q.push(N);
    dist[N] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        int one = N - v;
        // [1, one] as 1s  [one + 1, N] are 0
        int onecnt = 0;
        vector<int> vc = vector<int>(N + 1, 0);
        for (i = 1; i <= one; ++i) {
            vc[i] = 1;
            onecnt++;
        }

        for (i = 1; i <= K; ++i) {
            int pre = vc[i];
            vc[i] ^= 1;
            onecnt += vc[i] - pre;
        }

        for (i = K; i <= N; ++i) {
            int zerocount = N - onecnt;
            if (!visited[zerocount] && dist[zerocount] > dist[v] + 1) {
                dist[zerocount] = dist[v] + 1;
                pre[zerocount] = v;
                q.push(zerocount);
            }
            // move the mask from 
            if (i != N) {
                int pre = vc[i-K+1];
                vc[i-K+1] ^= 1;
                onecnt += vc[i-K+1] - pre;
                pre = vc[i+1];
                vc[i+1] ^= 1;
                onecnt += vc[i+1] - pre;
            }
        }
    }

    if (dist[0] < inf) {
        int v = 0;
        while (v != -1) {
            path.push_back(N - v);
            v = pre[v];
        }

        reverse(path.begin(), path.end());
    }

    return path;
}

int query(vector<int> &state, int curr, int nxt) {
    // we have curr many 1s, and (N - curr) many 0s
    // we want to transform to nxt many 1s
    // suppose we want to cover x 1s, and (K - x) 0s
    // (K - x) + (curr - x) = nxt
    int x = (K + curr - nxt) / 2, x2 = K - x;
    vector<int> q;
    for (int i = 1 ; i <= N; ++i) {
        if (x > 0 && state[i] == 1) {
            x--;
            q.push_back(i);
            state[i] ^= 1;
        } else if (x2 > 0  && state[i] == 0) {
            x2--;
            q.push_back(i);
            state[i] ^= 1;
        }
    }

    cout << "?";
    for (auto v : q) {
        cout << " " << v;
    }
    cout << endl;
    cin >> nxt;
    return nxt;
}

int main() {
    cin >> N >> K;
    auto path = BFS();
    if (path.empty()) {
        cout << -1 << endl;
        return 0;
    }

    int sz = path.size();
    int ans = 0;
    vector<int> state = vector<int>(N + 1, 0);
    for (int i = 0 ; i < sz - 1; ++i) {
        ans ^= query(state, path[i], path[i+1]);
    }

    cout << "! " << ans << endl;
    return 0;
}