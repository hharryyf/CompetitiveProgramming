#include <bits/stdc++.h>
#define MAX_SIZE 52
using namespace std;
typedef long long ll;
int f[MAX_SIZE];

struct edge {
    int u, v;
    ll w;
    bool ok = false;
    bool operator < (edge other) const {
        return w < other.w;
    }
};

edge edg[311];
int N, M;
int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}


void unionset(int a, int b) {
    int x = find(a), y = find(b);
    f[x] = y;
}

vector<int> wt;
vector<int> disc;
vector<ll> ret;
vector<int> up, down;
void solve(int idx) {
    vector<edge> e;
    ret.push_back(0);
    up.push_back(0);
    down.push_back(0);
    for (int i = 0 ; i < M; ++i) {
        edge ee;
        ee.u = edg[i].u, ee.v = edg[i].v, ee.w = 1ll * abs(edg[i].w - disc[idx]), ee.ok = edg[i].w >= disc[idx];
        e.push_back(ee);
    }

    for (int i = 1; i <= N; ++i) f[i] = i;
    sort(e.begin(), e.end());

    for (auto ee : e) {
        if (find(ee.u) != find(ee.v)) {
            unionset(ee.u, ee.v);
            ret[idx] += ee.w;
            if (ee.ok) {
                down[idx]++;
            } else {
                up[idx]++;
            }
        }
    }
    
    printf("x= %I64d, mst= %I64d\n", disc[idx], ret[idx]);
}

void linearsolve(ll a, ll b) {
  if (abs(a-b) % 2 == 1) {
    wt.push_back((a+b)/2 + 1);
  } else {
    wt.push_back((a+b)/2);
    wt.push_back((a+b)/2 + 1);
  }
}

ll getans(ll x) {
    if (x <= disc.front()) {
        return ret.front() + 1ll * (disc.front() - x) * (N - 1);
    } else if (x >= disc.back()) {
        return ret.back() + 1ll * (x - disc.back()) * (N - 1);
    }

    int idx = upper_bound(disc.begin(), disc.end(), x) - disc.begin() - 1;
    return ret[idx] + 1ll * (x - disc[idx]) * (up[idx] - down[idx]);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%lld", &edg[i].u, &edg[i].v, &edg[i].w);
        wt.push_back(edg[i].w);
        wt.push_back(edg[i].w + 1);
    }

    
    for (int i = 0 ; i < M; ++i) {
        for (int j = 0 ; j < i; ++j) {
            // |x - edg[i].w|  = |x - edg[j].w|
            if (edg[i].w == edg[j].w) continue;
            linearsolve(edg[i].w, edg[j].w);
        }
    }

    sort(wt.begin(), wt.end());
    for (int i = 0 ; i < (int) wt.size(); ++i) {
        if (i == 0 || wt[i] != wt[i-1]) disc.push_back(wt[i]);
    }

    int sz = disc.size();

    for (int i = 0 ; i < sz; ++i) {
        solve(i);
    }

    ll ans = 0;
    int p, k;
    ll q, a, b, c;
    scanf("%d%d%lld%lld%lld", &p, &k, &a, &b, &c);
    for (int i = 0 ; i < p; ++i) {
        scanf("%lld", &q);
        ans ^= getans(q);
        printf("query %lld ans= %lld\n", q, ans);
    }

    for (int i = p; i < k; ++i) {
        q = (q * a + b) % c;
        
        ans ^= getans(q);
    
        printf("query %lld ans= %lld\n", q, ans);
        
    }

    printf("%lld\n", ans);
    return 0;
}