#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N;
        scanf("%d", &N);
        map<int, vector<int>> mp, mp2;
        for (int i = 1 ; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            mp[v].push_back(i);
            mp2[v].push_back(i);
        }

        bool bad = false;
        map<int, int> ans;
        for (auto iter : mp) {
            if ((int) iter.second.size() == 1) {
                bad = true;
                break;
            }
            
            rotate(mp2[iter.first].begin(), mp2[iter.first].begin() + 1, mp2[iter.first].end());
            int sz = iter.second.size();
            for (int i = 0 ; i < sz; ++i) {
                ans[iter.second[i]] = mp2[iter.first][i];
            }
        }
        
        if (bad) {
            printf("-1\n");
            continue;
        }

        for (auto v : ans) {
            printf("%d ", v.second);
        }
        printf("\n");
    }
    return 0;
}