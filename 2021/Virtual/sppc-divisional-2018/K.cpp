#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int visited[MAX_SIZE];
vector<int> g1[MAX_SIZE];
vector<int> g2[MAX_SIZE];
int ans[MAX_SIZE];

void dfs1(int v) {
    visited[v] = 1;
    for (auto nv : g1[v]) {
        if (!visited[nv]) dfs1(nv);
    }
}

void dfs2(int v) {
    visited[v] = 1;
    for (auto nv : g2[v]) {
        if (!visited[nv]) dfs2(nv);
    }
}

int main() {
    int N, M1, M2, i;
    scanf("%d%d%d", &N, &M1, &M2);
    for (i = 0 ; i < M1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g1[u].push_back(v);
        g1[v].push_back(u);
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    for (i = 0 ; i < M2; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        g1[u].push_back(v);
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    dfs2(1);
    for (i = 2; i <= N; ++i) {
        if (!visited[i]) ans[i] = 2; 
    }

    memset(visited, 0, sizeof(visited));
    dfs1(1);

    for (i = 2; i <= N; ++i) {
        if (!visited[i] && ans[i] == 0) ans[i] = 1; 
    }

    for (i = 1; i <= N; ++i) {
        if (ans[i] == 0) {
            printf("No Ticket\n");
        } else if (ans[i] == 1) {
            printf("Ticket\n");
        } else {
            printf("Impossible\n");
        }
    }
    return 0;   
}