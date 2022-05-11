#include <bits/stdc++.h>
using namespace std;
int N, S;
vector<double> dp;
char st[2];

vector<char> pos = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
set<int> fix;

int mp(char ch) {
    if (ch >= '2' && ch <= '9') return ch - '0';
    if (ch == 'A') return 11;
    return 10;
}

int main() {
    int i, j;
    while (scanf("%d%d", &N, &S) != EOF) {
        fix.clear();
        dp.clear();
        dp.push_back(0);
        fix.insert(S);
        int lst = S;
        for (i = 1; i <= S; ++i) {
            dp.push_back(0);
        }

        for (i = 0 ; i < N; ++i) {
            scanf("%s", st);
            if (i == N - 1) continue;
            int nxt = mp(st[0]);
            for (j = 0 ; j < nxt; ++j) {
                dp.push_back(0);
            }
            fix.insert(lst);
            lst += nxt;
        }

        int sz = dp.size();
        dp[sz - 1] = 1;
        for (i = 0; i < 12; ++i) dp.push_back(0);
        for (i = sz - 2; i >= 1; --i) {
            if (fix.find(i) != fix.end()) dp[i] = 1;
            else {
                for (auto v : pos) {
                    dp[i] += (1.0 / (int) pos.size()) * dp[i + mp(v)];
                }
            }
        }

        double ans = 0.0;
        for (i = 1; i <= 10; ++i) {
            ans += 0.1 * dp[i];
        }

        printf("%.20lf\n", ans);
    }
    return 0;
}