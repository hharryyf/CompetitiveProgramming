/*
    This code would get TLE
    The time limit of the problem is insane, I can't see any reason except the author is an idiot to set the time limit
    to be 2s instead of 4
*/
// #define D
#define MAX_SIZE 200011
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

struct Trie {
    struct node {
        int child[2];
        int idx, cnt;
        int parent;
        bool leaf;
    };

    int cnt = 1;
    int root = 1;
    node tree[MAX_SIZE * 33];

	void add(int x, int id=-1) {
        int i, rt = root;
		for (i = 30; i >= 0; --i) {
            if (tree[rt].child[(x >> i) & 1]) {
                rt = tree[rt].child[(x >> i) & 1];
            } else {
                tree[rt].child[(x >> i) & 1] = ++cnt;
                tree[cnt].parent = rt;
                rt = cnt;
            }
        }

        tree[rt].leaf = true;
        tree[rt].cnt++;
        tree[rt].idx = id;

        while (rt != 1) {
            if (!tree[rt].leaf) {
                tree[rt].cnt = tree[tree[rt].child[0]].cnt + tree[tree[rt].child[1]].cnt;
            }
            rt = tree[rt].parent;
        }
	}
	
	void del(int x) {
		int i, rt = root;
		for (i = 30; i >= 0; --i) {
            if (tree[rt].child[(x >> i) & 1]) {
                rt = tree[rt].child[(x >> i) & 1];
            } else {
                return;
            }
        }

        tree[rt].cnt--;

        while (rt != 1) {
            if (!tree[rt].leaf) {
                tree[rt].cnt = tree[tree[rt].child[0]].cnt + tree[tree[rt].child[1]].cnt;
            }
            rt = tree[rt].parent;
        }
	}

    pair<int, int> query(int x) {
        int i, rt = root, ret = 0;
		for (i = 30; i >= 0; --i) {
            ret = ret << 1;
            if (tree[tree[rt].child[(x >> i) & 1]].cnt) {
                rt = tree[rt].child[(x >> i) & 1];
            } else {
                rt = tree[rt].child[((x >> i) & 1) ^ 1];
                ++ret;
            }
        }

        return make_pair(ret, tree[rt].idx);
	}
};

Trie t;

int a[MAX_SIZE];
int f[MAX_SIZE];
vector<int> comp[MAX_SIZE];
int N;
vector<int> disc;

array<int, 3> edg[MAX_SIZE];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int fx = find(x), fy = find(y);
    if (comp[fx].size() < comp[fy].size()) swap(fx, fy);
    // merge fy --> fx
    f[fy] = fx;
    for (auto v : comp[fy]) comp[fx].push_back(v);
    comp[fy].clear();
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + N);

    disc.push_back(0);

    for (i = 1; i <= N; ++i) {
        if (i == 1 || a[i] != a[i-1]) disc.push_back(a[i]);
    }

    N = (int) disc.size() - 1;

    int cnt = 0;
    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        t.add(disc[i], i);
        f[i] = i;
        comp[i].push_back(i);
        cnt++;
    }

    while (cnt > 1) {
        int idx = 0;
        for (i = 1; i <= N; ++i) {
            if (comp[i].empty()) continue;

            for (auto v : comp[i]) {
                t.del(disc[v]);
            }

            array<int, 3> ne = {-1, -1, 2000000000};
            for (auto v : comp[i]) {
                auto p = t.query(disc[v]);
                if (ne[0] == -1 || p.first < ne[2]) {
                    ne[0] = v;
                    ne[1] = p.second;
                    ne[2] = p.first;
                }
            }
            
            if (ne[0] != -1) {
                edg[++idx] = ne;
            }

            for (auto v : comp[i]) {
                t.add(disc[v], v);
            }
        }

        while (idx > 0) {
            auto &e = edg[idx--];
            if (find(e[0]) != find(e[1])) {
                cnt--;
                unionset(e[0], e[1]);
                ans += e[2];
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}