#include <bits/stdc++.h>
#define MAX_SIZE 2011
typedef int ll;
const ll INF = 1e7;
using namespace std;

struct Maxflow {
    struct edge {
    	int from, to;
    	ll flow, capacity;
    };
    
    // start and end point
    int s, t;
    
    // list array
    vector<edge> edg;
    
    // g reference to the ith vertex's edges
    vector<int> g[MAX_SIZE];
    
    // distance array and visited array
    int dist[MAX_SIZE], visited[MAX_SIZE];
    int cur[MAX_SIZE];
    
    void init() {
    	edg.clear();
    	int i;
    	for (i = 0 ; i < MAX_SIZE; i++) {
    		g[i].clear();
    	}
    }
    
    void addedge(int from, int to, ll capacity) {
    	edge e1 = edge{from, to, 0ll, capacity};
    	edge e2 = edge{to, from, 0ll, 0ll};
    	edg.push_back(e1), edg.push_back(e2);
    	g[from].push_back((int) edg.size() - 2);
    	g[to].push_back((int) edg.size() - 1);
    }
    
    // construct the level graph
    bool bfs() {
    	memset(visited,0,sizeof(visited));
    	memset(dist,0,sizeof(dist));
    	queue<int> q;
    	q.push(s);
    	visited[s] = 1;
    	dist[s] = 0;
    	while (!q.empty()) {
    		int v = q.front();
    		q.pop();
    		for (int i = 0 ; i < (int) g[v].size(); i++) {
    			edge &e = edg[g[v][i]];
    			int nxt = e.to;
    			if (!visited[nxt] && e.capacity > e.flow) {
    				dist[nxt] = dist[v] + 1;
    				q.push(nxt);
    				visited[nxt] = 1;
    			}  
    		}
    	}
    	
    	return visited[t];
    }
    
    ll dfs(int x, ll cp) {
    	if (x == t || cp == 0) {
    		return cp;
    	}
    	
    	ll flow = 0, newflow;
    	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
    		edge &e = edg[g[x][y]];
    		if (dist[x] + 1 == dist[e.to]) {
    			ll minn = min(cp, e.capacity - e.flow);
    			newflow = dfs(e.to, minn);
    			if (newflow > 0) {
    				e.flow += newflow;
    				edg[g[x][y] ^1].flow -= newflow;
    				flow += newflow;
    				cp -= newflow;
    				
    				if (cp == 0) {
    					break;
    				}
    			}
    		}
    	}
    	
    	return flow;
    }
    
    ll Dinic(){
        ll flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow += dfs(s,INF);
        }
        return flow;
    }
};

Maxflow mf;
int R, L, N;
int x[MAX_SIZE], y[MAX_SIZE];
int in(int v) {
    return v * 2;
}

int out(int v) {
    return v * 2 + 1;
}

bool check(int curr) {
    mf.init();
    int i, j, target = MAX_SIZE - 2;
    mf.s = 0, mf.t = MAX_SIZE - 1;
    mf.addedge(target, mf.t, 4);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (i == j) continue;
            if (1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]) <= 1ll * (curr + 2) * (curr + 2)) {
                mf.addedge(out(i), in(j), 1);
            }
        }

        if (1ll * x[i] * x[i] + 1ll * y[i] * y[i] <= 1ll * (curr + R + 1) * (curr + R + 1)) mf.addedge(mf.s, in(i), 1);
        if ((L - curr - 1 <= 0) || (1ll * (L - curr - 1) * (L - curr - 1) <= 1ll * x[i] * x[i] + 1ll * y[i] * y[i])) {
            mf.addedge(out(i), target, 1);
        }

        mf.addedge(in(i), out(i), 1);
    }

    if (curr >= L - R) mf.addedge(mf.s, target, 4);

    return mf.Dinic() == 4;
}

int main() {
    int i;
    scanf("%d%d%d", &L, &R, &N);
    for (i = 1; i <= N; ++i) scanf("%d%d", &x[i], &y[i]);
    int low = 0, high = 1e9, ans = 1e9;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}