#include <bits/stdc++.h>
#define SUBMIT
using namespace std;

/*
    This problem seems ridiculous, but it is a very common linear programming technique, another related problem is
    https://www.luogu.com.cn/problem/P3980 (in Chinese).
    Let xi = 1 be select s[i], otherwise, we select e[i]
    The initial observation is we can take all e[i] and for each xi taken, we get s[i] - e[i] 
    ms <= x1 + x2 + ... + x_(k) <= k - me
    ms <= x2 + x3 + .... + x_(k+1) <= k - me
    ...
    ms <= x_(n-k+1) + x_(n-k+2) + ... + x_n <= k - me 
    we want to maximize sum(xi(s[i] - e[i]), i = 1..n)
    The idea is to use MCMF to solve this special system of linear programming
    we rewrite the inequalities
    ms + Y[1] = x1 + x2 + ... + x_(k) = k - me - Z[1]                ....(1)
    ms + Y[2] = x2 + x3 + .... + x_(k+1) = k - me - Z[2]             ....(2)
    ms + Y[3] = x3 + x4 + .... + x_(k+2) = k - me - Z[3]             ....(3)
    ms + Y[4] = x4 + x5 + .... + x_(k+3) = k - me - Z[4]             ....(4)
    ...
    ms + Y[n-k] = x_(n-k) + ...+ x_(n-1) = k - me - Z[n-k]           ....(n-k)
    ms + Y[n-k+1] = x_(n-k+1) + ... + x_(n) = k - me - Z[n-k+1]              ....(n-k+1)

    we can rearrange the equations we obtain 2k equations (aim of this step each Y[i], Z[i] and xi appears once on the left and once on the right):
    x1 + x2 + ... + xk             = ms + Y[1]                       ....(1)
    Y[1] + Z[1]                    = k - me - ms                     ....(2)
    x_(k+1) + k - ms - me          = x1 + Y[2] + Z[1]                ....(3)
    Y[2] + Z[2]                    = k - me - ms                     ....(4)
    x_(k+2) + k - ms - me          = x2 + Y[3] + Z[2]                ....(5)
    ... 
    x_(n) + k - ms - me            = x_(n-k) + Y[n-k+1] + Z[n-k]     ....(2n-2k+1)
    Y[n-k+1] + Z[n-k+1]            = k - me - ms                     ....(2n-2k+2)
    k - me                         = x_(n-k+1) + ... + x_(n) + Z[n-k+1]   ....(2n-2k+3)
    treat each equation as a vertex and each variable as an edge
    if xi occurs on the left in equation e1 and on the right in equation e2, add edge e1->e2 with capacity 1 and cost - e[i] + s[i] (since we want min-cost)
    in details, we add edge (1, 3), (1, 5) ... (1, 2k + 1) for x1 to xk
                   add edge (3, 2k + 3), (5, 2k+5) ... (2n-4k+1, 2n-2k+1) for x_(k+1) to x_(n-k)
                   add edge (2n-4k+3, 2n-2k+3), (2n-4k+5, 2n-2k+3) ... (2n-2k+1, 2n-2k+3) for x_(n-k+1) to x_(n)
    if Y[i] occurs on the left in equation e1 and on the right in equation e2, add edge e1->e2 with capcity inf and cost 0
    in details, we add edge (i, i-1)
    if Z[i] occurs on the left in equation e1 and on the right in equation e2, add edge e1->e2 with capacity inf and cost 0
    in details, we add edge (i, i+1)
    if a constant occurs on the left of the equation e, we add an edge e->target with capacity constant and cost 0
    in details, we add (3, 5, 7, 9, ... 2n-2k+1, 2n-2k+3 -> T)
    if a constant occurs on the right of the equation e, we add an edge src->e with capacity constant and cost 0 
    in details, we add (1, 2, 4, 6, 8, ... 2n-2k + 2 -> T)
    Now, "just" run MCMF and done.
*/

typedef long long ll;
const ll INF = 1e16;
const int maxn = 2111;

struct Edge {
    int from, to;
	ll cap, flow, cost;
    int id;
    Edge(int u, int v, ll c, ll f, ll w, int id):from(u),to(v),cap(c),flow(f),cost(w), id(id)
    {}
};

struct MCMF {
    int n, m;
    int src, target;
    vector<Edge> edges; 
    vector<int> G[maxn]; 
    int inq[maxn]; 
    ll d[maxn]; 
    int p[maxn]; 
    ll a[maxn]; 

    MCMF() {}

    void init(int n=maxn) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addedge(int from, int to, ll cap, ll cost, int id=-1) {
        edges.push_back(Edge(from, to, cap, 0, cost, id)); 
        edges.push_back(Edge(to, from, 0, 0, -cost, -1)); 
        m = edges.size();
        G[from].push_back(m-2); 
        G[to].push_back(m-1);
    }

    bool SPFA(int s, int t, ll &flow, ll &cost) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for(int i = 0; i < (int) G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if(d[t] == INF) return false; 
        flow += a[t]; 
        cost += d[t] * a[t]; 
        for(int u = t; u != s; u = edges[p[u]].from) {
        		edges[p[u]].flow += a[t]; 
        		edges[p[u]^1].flow -= a[t];
		}
        return true;
    }

    ll mincostMaxflow(ll &cost) {
        ll flow = 0; 
		cost = 0;
        while(SPFA(src, target, flow, cost));
        return flow;
    }
};

MCMF mf;
int N, K, ms, me;
ll s[maxn], e[maxn];
bool sel[maxn];

void openfile() {
    freopen("delight.in", "r", stdin);
    freopen("delight.out", "w", stdout);
}

int main() {
    #ifdef SUBMIT
    openfile();
    #endif
    int i, j, k, tolequation;
    ll cost = 0, ret = 0;
    scanf("%d%d%d%d", &N, &K, &ms, &me);
    for (i = 1; i <= N; ++i) scanf("%lld", &s[i]);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &e[i]);
        ret += e[i];
    }

    mf.init();
    mf.src = maxn - 2, mf.target = maxn - 1;
    tolequation = 2 * N - 2 * K + 3;
    // deal with the constant terms
    mf.addedge(mf.src, 1, ms, 0);
    mf.addedge(tolequation, mf.target, K - me, 0);
    for (i = 3; i < tolequation; i = i + 2) {
        mf.addedge(i, mf.target, K - ms - me, 0);
    }

    for (i = 2; i <= tolequation; i = i + 2) {
        mf.addedge(mf.src, i, K - ms - me, 0);
    }

    // deal with the X[i] edges
    for (i = 1; i <= K; ++i) {
        mf.addedge(1, min(2 * i + 1, tolequation), 1, e[i] - s[i], i);
    }

    for (i = K + 1, j = 3, k = 2 * K + 3; i <= N; ++i, j = j + 2, k = k + 2) {
        mf.addedge(j, min(k, tolequation), 1, e[i] - s[i], i);
    }

    // deal with the Y[i] and Z[i] edges
    for (j = 2; j < tolequation; j = j + 2) {
        mf.addedge(j, j - 1, INF, 0);
    }

    for (j = 2; j < tolequation; j = j + 2) {
        mf.addedge(j, j + 1, INF, 0);
    }
    mf.mincostMaxflow(cost);
    printf("%lld\n", -cost + ret);
    for (auto e : mf.edges) {
        if (e.id != -1 && e.flow == e.cap) {
            sel[e.id] = true;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (sel[i]) {
            printf("S");
        } else {
            printf("E");
        }
    }
    printf("\n");
    return 0;
}