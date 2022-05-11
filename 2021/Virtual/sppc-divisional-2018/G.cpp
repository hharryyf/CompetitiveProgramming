#include <bits/stdc++.h>

using namespace std;
char s[55];

int main() {
    int N;
    scanf("%s", s);
    N = strlen(s);
    int i;
    for (i = N - 1; i >= 0; --i) {
        printf("%c%c%c", s[i], s[i], s[i]);
    }
    printf("\n");
    return 0;
}