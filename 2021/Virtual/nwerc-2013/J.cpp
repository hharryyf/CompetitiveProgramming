#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;

vector<int> g[MAX_SIZE];
int tol[MAX_SIZE], tolb[MAX_SIZE];
char s[MAX_SIZE * 2];
int idx = 1, L[MAX_SIZE], R[MAX_SIZE];

void dfs(int l, int r, int id=1) {
    //printf("%d %d\n", l, r);
    if (l >= r) return;
    if (r - l == 1) {
        tol[id] = 1;
        tolb[id] = 0;
        //printf("empty at %d\n", id);
        return;
    }

    if (r - l == 2) {
        tol[id] = 1;
        tolb[id] = 1;
        //printf("ball at %d\n", id);
        return;
    } 

    int l1 = l + 1, r1 = R[l+1], l2 = L[r-1], r2 = r-1;
    g[id].push_back(idx + 1);
    g[id].push_back(idx + 2);
    //cout << "Addedge " << id << " " << idx + 1 << endl;
    //cout << "add edge " << id << " " << idx + 2 << endl;
    int curr = idx;
    idx += 2;
    dfs(l1, r1, curr + 1);
    dfs(l2, r2, curr + 2);
    tol[id] = tol[curr + 1] + tol[curr + 2];
    tolb[id] = tolb[curr + 1] + tolb[curr + 2]; 
}

int solve(int idx, int target) {
    if (tol[idx] < target) return MAX_SIZE;
    if (target == 0) return 0;
    if (g[idx].empty() && target == 1) return tolb[idx] < 1;
    if (target % 2 == 1) {
        int l = solve(g[idx][0], target / 2) + solve(g[idx][1], target / 2 + 1);
        int r = solve(g[idx][0], target / 2 + 1) + solve(g[idx][1], target / 2);
        return min(l, r);
    }

    return solve(g[idx][0], target >> 1) + solve(g[idx][1], target >> 1);
}

int main() {
    while (scanf("%s", s) != EOF) {
        int i, len = strlen(s);
        int cnt = 0;
        idx = 1;
        for (i = 0 ; i < len; ++i) {
            if (s[i] == 'B') {
                ++cnt;
            }
        }

        for (i = 1 ; i < MAX_SIZE; ++i) {
            g[i].clear();
            tol[i] = tolb[i] = 0;
        }

        stack<int> st;
        for (i = 0 ; i < len; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                L[i] = st.top();
                R[st.top()] = i;
                st.pop();
            }
        }

        dfs(0, len - 1);
        //printf("%d %d\n", tolb[1], tol[1]);
        // printf("parse success\n");
        int ans = solve(1, cnt);
        if (ans >= MAX_SIZE) {
            printf("impossible\n");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}