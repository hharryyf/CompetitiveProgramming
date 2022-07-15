#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 300011
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

vector<int> query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    vector<int> ret;
    int i;
    for (i = l; i <= r; ++i) {
        int x;
        cin >> x;
        ret.push_back(x);
    }

    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N;
        scanf("%d", &N);
        int low = 1, high = N;
        int ans = 1;
        for (int i = 1; i <= 15; ++i) {
            int mid = (low + high) / 2;
            if (low > high) break;
            auto ret = query(low, mid);
            int good = mid - low + 1;
            for (auto v : ret) {
                if (v > mid || v < low) {
                    good--;
                }
            }

            if (good % 2 == 1) {
                high = mid;
                ans = mid;
            } else {
                low = mid + 1;
            }
        }
        
        cout << "! " << ans << endl;
    }
    return 0;
}