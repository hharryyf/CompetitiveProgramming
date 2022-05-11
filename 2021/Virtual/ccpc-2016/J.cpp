#include <bits/stdc++.h>

using namespace std;

list<string> q[5];
list<string> ecl; 
char st[7];

set<string> advanced;
list<string> tmpq[5];
list<string> tmpecl;

bool simulate(int X, int Y, string target) {
    int i;
    advanced.clear();
    for (i = 0 ; i < 5; ++i) {
        tmpq[i].clear();
        tmpecl.clear();
    }

    for (i = 0 ; i < 5; ++i) {
        for (auto v : q[i]) {
            tmpq[i].push_back(v);
        }
    }

    for (auto v : ecl) tmpecl.push_back(v);
    while (X > 0) {
        for (i = 0 ; i < 5 && X > 0; ++i) {
            if (!tmpq[i].empty()) {
                auto ss = tmpq[i].front();
                tmpq[i].pop_front();
                if (advanced.find(ss) == advanced.end()) {
                    advanced.insert(ss);
                    --X;
                }

                //cout << ss << " " << target << endl;
                if (ss == target) {
                    return true;
                }
            }
        }
    }

    while (Y > 0 && !tmpecl.empty()) {
        auto ss = tmpecl.front();
        tmpecl.pop_front();
        if (advanced.find(ss) == advanced.end()) {
            advanced.insert(ss);
            Y--;
        }

        if (ss == target) return true;
    }

    return false;
}

void solve(int G, string target) {
    int i, j;
    advanced.clear();
    for (i = 0 ; i < 5; ++i) {
        q[i].clear();
    }

    ecl.clear();

    for (i = 0 ; i < 5; ++i) {
        for (j = 0 ; j < 20; ++j) {
            scanf("%s", st);
            q[i].push_back(string(st));
        }
    }

    for (j = 0 ; j < 20; ++j) {
        scanf("%s", st);
        ecl.push_back(string(st));
    }

    for (i = 0; i <= G; ++i) {
        if (!simulate(G - i, i, target)) {
            printf("%d\n", i);
            return;
        }
    }

    printf("ADVANCED!\n");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int G;
        string target;
        scanf("%d%s", &G, st);
        target = string(st);
        solve(G, target);
    }
    return 0;
}