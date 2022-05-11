#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE];
int N, L;

int main() {
    int len = 0;
    scanf("%d%d", &N, &L);
    for (int i = 0 ; i < N; ++i) {
        scanf("%s", s);
        len += strlen(s);
    }

    if (len > L) {
        printf("No\n");
        return 0;
    } 

    if (len == L && N == 1) {
        printf("Yes\n");
        return 0;
    }

    if (len == L) {
        printf("No\n");
        return 0;
    }

    if (N == 1) {
        printf("No\n");
        return 0;
    }

    if ((L - len) % (N - 1) == 0) {
        printf("Yes\n");
        return 0;
    }

    printf("No\n");
    return 0;
}