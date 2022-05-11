
#include <bits/stdc++.h>
using namespace std;
char st[2];
int query(int x, int y) {
    printf("? %d %d\n", x, y);
    fflush(stdout);
    scanf("%s", st);
    if (st[0] == '>') return 1;
    return -1;
}

int getmin(set<int> &s) {
    vector<int> ret;
    for (auto v : s) ret.push_back(v);
    int i, v = ret[0];
    for (i = 1; i < (int) ret.size(); ++i) {
        if (query(v, ret[i]) == 1) v = ret[i];
    } 

    return v;
}

int main() {
    int T, N, i, v, u;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        set<int> s1, s2;
        for (i = 1; i <= N - 1; ++i) s1.insert(i);
        s2.insert(N);
        s2.insert(N + 1);
        for (i = N + 2; i <= N * 2; ++i) {
            v = getmin(s1), u = getmin(s2);
            if (query(v, u) == 1) {
                s2.erase(u);
            } else {
                s1.erase(v);
            }

            if (s1.size() < s2.size()) {
                s1.insert(i);
            } else {
                s2.insert(i);
            }
        }

        v = getmin(s1), u = getmin(s2);
        if (query(v, u) == 1) {
            s2.erase(u);
        } else {
            s1.erase(v);
        }
        printf("!\n");
        fflush(stdout);
    }
    return 0;
}