#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int cmpid[MAX_SIZE];
vector<int> g[MAX_SIZE];
int low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> s;
set<int> h[MAX_SIZE];
int k = 1, cid = 1;
int N;

void tarjan(int v, int pre) {
    visited[v] = k++;
    low[v] = visited[v];
    s.push(v);
    instack[v] = 1;
    for (auto nv : g[v]) {
        if (nv != pre) {
            if (!visited[nv]) {
                tarjan(nv, v);
                low[v] = min(low[v], low[nv]);
            } else if (instack[nv]) {
                low[v] = min(low[v], visited[nv]);
            }
        }
    }

    if (low[v] == visited[v]) {
        while (s.top() != v) {
            cmpid[s.top()] = cid;
            instack[s.top()] = 0;
            s.pop();
        }

        cmpid[s.top()] = cid++;
        instack[s.top()] = 0;
        s.pop();
    }
}


void construct() {
    for (int i = 0 ; i < N; ++i) {
        for (auto nv : g[i]) {
            if (cmpid[i] != cmpid[nv]) {
                h[cmpid[i]].insert(cmpid[nv]);
            }
        }
    }

    int ans = -1;
    for (int i = 1; i < cid; ++i) {
        if ((int) h[i].size() <= 1) ans++;
    }

    printf("%d\n", ans);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            int u;
            scanf("%d", &u);
            g[u].push_back(i);
            g[i].push_back(u);
        }
    }

    for (i = 0 ; i < N; ++i) {
        if (!visited[i]) {
            tarjan(i, -1);
        }
    }

    construct();
    return 0;   
}