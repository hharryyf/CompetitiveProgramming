#include <bits/stdc++.h>

using namespace std;

int N;
int a[262192][2];
int deg[262192];

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 0; i < (1 << N) - 1; ++i) {
        scanf("%d%d", &a[i][0], &a[i][1]);
        deg[a[i][0]]++;
        deg[a[i][1]]++;
    }

    for (i = N - 1 ; i >= 0; --i) {
        int cnt = 0;
        //cout << "check round " << i << endl;
        set<int> st;
        for (j = 0 ; j < (1 << N) - 1; ++j) {
            if (a[j][0] == a[j][1]) {
                printf("MISTAKE\n");
                return 0;
            }

            if ((min(deg[a[j][0]], deg[a[j][1]]) == 1 && max(deg[a[j][0]], deg[a[j][1]]) != 1&& i != 0) 
               || (deg[a[j][0]] == 1 && deg[a[j][1]] == 1 && i == 0)) {
                cnt++;
                if (st.find(a[j][0]) != st.end() || st.find(a[j][1]) != st.end()) {
                    printf("MISTAKE\n");
                    return 0;
                }
                st.insert(a[j][0]);
                st.insert(a[j][1]);
            }
        }

        if (cnt != (1 << i)) {
            // cout << cnt << endl;
            printf("MISTAKE\n");
            return 0;
        }

        for (auto v : st) {
            deg[v]--;
        }
    }

    printf("OK\n");
    return 0;
}