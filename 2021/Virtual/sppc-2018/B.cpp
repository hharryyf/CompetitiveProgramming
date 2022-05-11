#include <bits/stdc++.h>
#define MAX_SIZE 6000111
using namespace std;

int N, p[MAX_SIZE];
char st[MAX_SIZE];

int KMP() {
    int i, j = 0;
    // printf("%d\n", N);
    p[1] = 0;
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }

    int ans = 0;
    for (i = N; i >= 1; --i) {
        if (st[i] == '#') break;
        ans = max(ans, p[i]);
    }

    return ans;
}

char s[MAX_SIZE];

int main() {
    int n, ans = 0, i;
    scanf("%s", s+1);
    n = strlen(s+1);
    for (i = 2; i <= n; i += 2) {
        st[++N] = s[i];
    }

    st[++N] = '#';
    for (i = 1; i <= n; ++i) {
        st[++N] = s[i];
    }
    //printf("%s\n", st + 1);
    ans = min(KMP() * 2 + 1, n);
    N = 0;
    for (i = 1; i <= n; i += 2) {
        st[++N] = s[i];
    }
    st[++N] = '#';
    for (i = 1; i <= n; ++i) {
        st[++N] = s[i];
    }  
    st[N + 1] = '\0';
    //printf("%s\n", st + 1);
    ans = min(max(KMP() * 2, ans), n);
    printf("%d\n", ans);
    return 0;
}