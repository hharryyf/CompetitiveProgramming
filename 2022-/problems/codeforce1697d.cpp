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


char ch[2];
string s;


int query(int l, int r) {
    #ifdef D
        int cnt = 0;
        set<char> st;
        printf("query %d, %d\n", l, r);
        for (int i = l - 1; i <= r - 1; ++i) st.insert(s[i]);
        return st.size(); 
    #endif 
    cout << "? 2 " << l << " " << r << endl;
    cin >> l;
    return l;
}

char getpos(int idx) {
    #ifdef D
        printf("Get position %d\n", idx);
        return s[idx-1];
    #endif
    cout << "? 1 " << idx << endl;
    scanf("%s", ch);
    return ch[0];
}

char p[MAX_SIZE];
int color[MAX_SIZE];
map<int, int> lst;

int main() {
    int N, i, pre = 0, cnt = 0;
    cin >> N;
    #ifdef D
        cin >> s;
    #endif
    for (i = 1; i <= N; ++i) {
        int curr = query(1, i);
        if (curr != pre) {
            ++cnt;
            color[i] = cnt;
            pre = curr;
        } else {
            vector<int> occ;
            for (auto iter : lst) {
                occ.push_back(iter.second);
            }

            sort(occ.begin(), occ.end());

            // query the last position such that query(occ[mid], i) = occ.size() - mid
            int low = 0, high = (int) occ.size() - 1, mid;
            while (low <= high) {
                mid = low + (high - low) / 2;
                int target = (int) occ.size() - mid;
                if (query(occ[mid], i) == target) {
                    color[i] = color[occ[mid]];
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        lst[color[i]] = i;
    }

    for (i = 1; i <= N; ++i) {
        debug("%d %d\n", i, color[i]);
    }

    for (auto iter : lst) {
        debug("ready color=%d\n", iter.first);
        auto c = getpos(iter.second);
        p[color[iter.second]] = c;
    }

    cout << "! ";
    
    for (i = 1; i <= N; ++i) {
        cout << p[color[i]];
    }

    cout << endl;
    return 0;
}