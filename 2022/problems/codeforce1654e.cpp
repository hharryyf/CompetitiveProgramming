#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 1000011
#define BLOCK 317
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

int N;
int a[MAX_SIZE];

int main() {
    scanf("%d", &N);
    int ans = N;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    // B * N * log(N)
    for (int i = -BLOCK; i <= BLOCK; ++i) {
        vector<int> disc;
        for (int j = 1; j <= N; ++j) {
            disc.push_back(a[j] - j * i);
        }

        sort(disc.begin(), disc.end());

        int cnt = 0;
        for (int j = 0 ; j < (int) disc.size(); ++j) {
            if (j == 0) cnt++;
            if (j > 0 && disc[j] == disc[j-1]) cnt++;
            if (j > 0 && disc[j] != disc[j-1]) {
                cnt = 1;
            }

            ans = min(ans, N - cnt);
        }
    }

    // N * 1e5 / B * log(1e5 / B)

    for (int i = 1; i <= N; ++i) {
        int low = max(1, i - 100000 / BLOCK);
        int high = min(N, i + 100000 / BLOCK);
        map<int, int> cnt;
        for (int j = low; j <= high; ++j) {
            if (j == i) continue;
            if ((a[j] - a[i]) % (j - i) == 0 && abs((a[j] - a[i]) / (j - i)) > BLOCK) {
                cnt[(a[j] - a[i]) / (j - i)]++;
                ans = min(ans, N - cnt[(a[j] - a[i]) / (j - i)] - 1);
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}