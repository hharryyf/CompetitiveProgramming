#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
set<int> h[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
stack<int> st;
map<int, int> match;
int cnt, N, M, indeg[MAX_SIZE], outdeg[MAX_SIZE];

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            instack[st.top()] = 0;
            cmpid[st.top()] = v;
            st.pop();
        }

        cmpid[st.top()] = v;
        instack[st.top()] = 0;
        st.pop();
    }
}


void init() {
    int i;
    for (i = 1; i <= N; ++i) {
        g[i].clear();
        h[i].clear();
        instack[i] = visited[i] = low[i] = cmpid[i] = 0;
        indeg[i] = outdeg[i] = 0;
    }

    match.clear();
    while (!st.empty()) st.pop();
    cnt = 0;
}

void dfs(int v, bool &fg, int &sk) {
    visited[v] = 1;
    if (fg) return;
    if (!outdeg[v]) {
        sk = v;
        fg = true;
        return;
    }

    for (auto nv : h[v]) {
        if (!visited[nv]) {
            dfs(nv, fg, sk);
        }
    }
}

int main() {
    int i;
    while (scanf("%d%d", &N, &M) != EOF) {
        init();
        for (i = 0 ; i < M; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
        }

        for (i = 1; i <= N; ++i) {
            if (!visited[i]) {
                tarjan(i);
            }
        }

        for (i = 1; i <= N; ++i) {
            for (auto nv : g[i]) {
                if (cmpid[i] != cmpid[nv]) {
                    h[cmpid[i]].insert(cmpid[nv]);
                }
            }
        }

        for (i = 1; i <= N; ++i) {
            for (auto nv : h[i]) {
                indeg[nv]++;
                outdeg[i]++;
            }
        }

        for (i = 1; i <= N; ++i) visited[i] = 0;

        vector<int> src, sink;
        cnt = 0;
        for (i = 1; i <= N; ++i) {
            if (cmpid[i] == i) {
                cnt++;
                if (indeg[i] == 0) {
                    src.push_back(i);
                } else if (outdeg[i] == 0) {
                    sink.push_back(i);
                }
            }
        }

        if (cnt == 1) {
            printf("0\n");
            continue;
        }

        vector<int> src1, sink1, src2, sink2;
        for (i = 0 ; i < (int) src.size(); ++i) {
            bool fg = false;
            int sk = -1;
            dfs(src[i], fg, sk);
            if (fg) {
                match[src[i]] = sk;
                match[sk] = src[i];
                src1.push_back(src[i]);
                sink1.push_back(sk);
            }
        }

        printf("%d\n", max((int) src.size(), (int) sink.size()));
        // add the sink to src edges and make the matchings fully connected
        for (i = 0; i < (int) src1.size(); ++i) {
            printf("%d %d\n", sink1[i], src1[(i + 1) % (int) src1.size()]);
        }

        for (auto v : src) {
            if (match.find(v) == match.end()) src2.push_back(v);
        }

        for (auto v : sink) {
            if (match.find(v) == match.end()) sink2.push_back(v);
        }

        if (src2.size() <= sink2.size()) {
            // connect all non-connected sink to the none connected src
            for (i = 0 ; i < (int) src2.size(); ++i) {
                printf("%d %d\n", sink2[i], src2[i]);
            }

            for (i = src2.size(); i < (int) sink2.size(); ++i) {
                printf("%d %d\n", sink2[i], sink1[0]);
            }
        } else {
            // connect all non-connected sink to the none connected src
            for (i = 0 ; i < (int) sink2.size(); ++i) {
                printf("%d %d\n", sink2[i], src2[i]);
            }

            for (i = sink2.size(); i < (int) src2.size(); ++i) {
                printf("%d %d\n", sink1[0], src2[i]);
            }
        }
    }
    return 0;
}