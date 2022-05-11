#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

char s[MAX_SIZE];
vector<int> g[MAX_SIZE];
set<int> h[MAX_SIZE];
int dp[MAX_SIZE], dp2[MAX_SIZE];
int cmpid[MAX_SIZE], low[MAX_SIZE], visited[MAX_SIZE], instack[MAX_SIZE];
set<int> univ[MAX_SIZE], exis[MAX_SIZE];
stack<int> st;
int cnt, N, M, cid = 1;

void init() {
    int i;
    cid = 1;
    cnt = 0;
    for (i = 0; i <= 2 * N + 1; ++i) {
        cmpid[i] = low[i] = visited[i] = instack[i] = 0;
        g[i].clear();
        h[i].clear();
        dp[i] = dp2[i] = 0;
        univ[i].clear();
        exis[i].clear();
    }
    while (!st.empty()) st.pop();
}

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
            cmpid[st.top()] = cid;
            st.pop();
        }
        cmpid[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();
    }
}

int pos(int x) {
    return x * 2;
}

int neg(int x) {
    return x * 2 - 1;
}

pair<int, int> cnf[MAX_SIZE];

bool isexist(int l) {
    return s[abs(l)] == 'E';
}

void addconstraint(int u, int v) {
    int p1 = u, p2 = v;
    if (p1 > 0) {
        p1 = neg(p1);
    } else {
        p1 = pos(-p1);
    }

    if (p2 > 0) {
        p2 = pos(p2);
    } else {
        p2 = neg(-p2);
    }

    g[p1].push_back(p2);
}

bool dfs(int v) {
    if (visited[v]) return dp[v];
    for (auto nv : h[v]) {
        dp[v] += dfs(nv);
    }

    visited[v] = 1;
    return dp[v];
}

bool solve() {
    int i;
    scanf("%d%d", &N, &M);
    scanf("%s", s + 1);
    init();
    for (i = 1; i <= M; ++i) {
        scanf("%d%d", &cnf[i].first, &cnf[i].second);
    }

    for (i = 1; i <= M; ++i) {
        if (abs(cnf[i].first) > abs(cnf[i].second)) swap(cnf[i].first, cnf[i].second);
        if (cnf[i].first + cnf[i].second == 0) continue;
        if (!isexist(cnf[i].first) && !isexist(cnf[i].second)) {
            return false;
        }

        if (!isexist(cnf[i].second)) {
            addconstraint(cnf[i].first, cnf[i].first);
        } else {
            addconstraint(cnf[i].first, cnf[i].second);
            addconstraint(cnf[i].second, cnf[i].first);
        }
    }

    for (i = 1; i <= 2 * N; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 1; i <= N; ++i) {
        if (isexist(i) && cmpid[pos(i)] == cmpid[neg(i)]) return false;
    }

    for (i = 1; i <= 2 * N; ++i) {
        for (auto v : g[i]) {
            if (cmpid[v] != cmpid[i]) {
                h[cmpid[i]].insert(cmpid[v]);
            }
        }
    }

    for (i = 1; i <= 2 * N; ++i) {
        visited[i] = 0;
        if (!isexist((i + 1) / 2)) {
            dp[cmpid[i]] += 1;
            dp2[cmpid[i]] += 1;
            univ[cmpid[i]].insert((i + 1) / 2);
        } else {    
            exis[cmpid[i]].insert((i + 1) / 2);
        }
    }
    for (i = 1; i <= 2 * N; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    for (i = 1; i <= 2 * N; ++i) {
        // printf("%d %d\n", i, dp[i]);
        if (dp[i] >= 2 && dp2[i] >= 1) return false;
    }

    for (i = 1; i <= 2 * N; ++i) {
        if (!univ[i].empty() && !exis[i].empty()) {
            if (*univ[i].rbegin() > *exis[i].begin()) return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        bool ret = solve();
        printf("%s\n", ret ? "TRUE" : "FALSE");
    }
    return 0;
}