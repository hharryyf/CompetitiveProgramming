#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 511
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
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
using namespace std;
typedef long long ll;

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

int query(int a, int b) {
    string s;
    cout << "? " << a << " " << b << endl;
    cin >> s;
    if (s == "Yes") {
        return 1;
    }

    return 0;
}

int N;
int deg[MAX_SIZE];

int main() {
    int i, j;
    cin >> N;
    queue<int> q;
    for (i = 1; i <= N; ++i) {
        cin >> deg[i];
        if (!deg[i]) q.push(i);
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (i = 1; i <= N; ++i) {
            if (deg[i]) {
                deg[i]--;
                if (!deg[i]) q.push(i);
            }
        }
    }

    int cnt = 0;
    for (i = 1; i <= N; ++i) {
        if (!deg[i]) {
            cnt++;
        }
    }

    if (cnt == N) {
        cout << "! 0 0" << endl;
        return 0;
    }

    vector<pair<int, pair<int, int>>> ops;
    for (i = 1; i <= N; ++i) {
        if (!deg[i]) continue;
        for (j = i + 1; j <= N; ++j) {
            if (!deg[j]) continue;
            if (deg[i] >= deg[j]) {
                ops.push_back(make_pair(abs(deg[i] - deg[j]), make_pair(i, j)));
            } else {
                ops.push_back(make_pair(abs(deg[i] - deg[j]), make_pair(j, i)));
            }
            
        }
    }

    sort(ops.begin(), ops.end());
    reverse(ops.begin(), ops.end());

    for (auto op : ops) {
        if (query(op.second.first, op.second.second)) {
            cout << "! " << op.second.first << " " << op.second.second << endl;
            return 0;
        }
    }

    cout << "! 0 0" << endl;
    return 0;
}