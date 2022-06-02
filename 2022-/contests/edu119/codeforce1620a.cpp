#pragma GCC optimize(3)
#include <bits/stdc++.h>

#define MAX_SIZE 300011
typedef long long ll;
using namespace std;


char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", s);
        int N = strlen(s);
        int ce = 0, cn = 0;
        for (int i = 0 ; i < N; ++i) {
            if (s[i] == 'E') ce++;
            else cn++;
        }
        
        if (ce == N - 1 && cn == 1) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}