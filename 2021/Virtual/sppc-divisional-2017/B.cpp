#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

char s[6][MAX_SIZE];
char ord[6][MAX_SIZE];

set<int> st[64]; 

int main() {
    int N, M, i, j;
    scanf("%d%d", &N, &M);
    for (i = 0; i < 6; ++i) {
        scanf("%s", s[i]+1);
    }

    for (i = 0 ; i < 6; ++i) {
        scanf("%s", ord[i]+1);
    }

    for (i = 1; i <= N; ++i) {
        int w = 0;
        for (j = 0 ; j < 6; ++j) {
            w = w * 2 + (s[j][i] - '0');
        }
        st[w].insert(i);
    }

    for (i = 1; i <= M; ++i) {
        int w = 0;
        for (j = 0 ; j < 6; ++j) {
            w = w * 2 + (ord[j][i] - '0');
        }

        int mx = -1;
        for (j = 0 ; j <= 63; ++j) {
            if (!st[j].empty() && ((j & w) == w)) {
                mx = max(*st[j].rbegin(), mx);
            }
        }

        if (mx == -1) {
            printf("-1");
        } else {
            for (j = 0 ; j <= 63; ++j) {
                if (!st[j].empty() && *st[j].rbegin() == mx) {
                    st[j].erase(mx);
                    printf("%d", mx);
                    break;
                }
            }
        }
        if (i != M) printf(" ");
    }
    printf("\n");
    return 0;
}