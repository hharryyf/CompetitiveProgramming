#include <bits/stdc++.h>
#define MAX_SIZE 204911
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
int N;
char s[12];
vector<int> g[111];
map<string, int> mp;
map<vector<int>, int> mp2;

int main() {
    int i, j, k, tol = 0;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            scanf("%s", s);
            string ss = string(s);
            if (mp.find(ss) == mp.end()) {
                mp[ss] = ++tol;
            }
            g[i].push_back(mp[ss]);
        }
        sort(g[i].begin(), g[i].end());
    }

    tol = 0;
    for (i = 0 ; i < N; ++i) {
        int sz = g[i].size();
        for (j = 1; j < (1 << sz); ++j) {
            vector<int> curr;
            for (k = 0 ; k < sz; ++k) {
                if (j & (1 << k)) {
                    curr.push_back(g[i][k]);
                }
            }

            if (mp2.find(curr) == mp2.end()) {
                mp2[curr] = ++tol;
            }
        }
    }

    for (i = 0 ; i < N; ++i) {
        int sz = g[i].size();
        for (j = 1; j < (1 << sz); ++j) {
            vector<int> curr;
            for (k = 0 ; k < sz; ++k) {
                if ((1 << k) & j) curr.push_back(g[i][k]);
            }
            int from = mp2[curr], sub;
            for (sub = j; sub > 0; sub = (sub - 1) & j) {
                if (sub == j) continue;
                curr.clear();
                for (k = 0; k < sz; ++k) {
                    if (sub & (1 << k)) {
                        curr.push_back(g[i][k]);
                    }
                }

                if ((int) curr.size() + 1 == __builtin_popcount(j)) {
                    int to = mp2[curr];
                    mf.addedge(from, to + tol, 1);
                }
            }
        }
    }

    mf.s = 0, mf.t = MAX_SIZE - 1;
    for (i = 1; i <= tol; ++i) {
        mf.addedge(mf.s, i, 1);
        mf.addedge(i + tol, mf.t, 1);
    }

    printf("%d\n", tol - mf.Dinic());
    return 0;
}