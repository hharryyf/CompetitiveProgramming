#include <bits/stdc++.h>
using namespace std;

int cent, N;
char s[11];

int parse(char ss[]) {
    int i, curr = 0;
    for (i = 0 ; i < (int) strlen(ss); ++i) {
        if (ss[i] >= '0' && ss[i] <= '9') {
            curr *= 10;
            curr += ss[i] - '0';
        }
    }

    return curr;
}

int main() {
    scanf("%d", &N);
    scanf("%s", s);
    cent = parse(s);
    int i, ans = 0;
    for (i = 0 ; i < N; ++i) {
        scanf("%s", s);
        cent += parse(s);
        // printf("%d\n", cent);
        if (cent % 100 != 0) ans++;
    }
    
    printf("%d\n", ans);
    return 0;
}