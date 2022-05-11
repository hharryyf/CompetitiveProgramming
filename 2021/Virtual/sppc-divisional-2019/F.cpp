#include <bits/stdc++.h>

using namespace std;
int N;
#define MAX_SIZE 200011
char s[MAX_SIZE], t[MAX_SIZE], org[MAX_SIZE];
void change(char a, char b) {
    for (int i = 0 ; i < N; ++i) {
        if (s[i] == a) {
            s[i] = b;
        }
    }
}

int score() {
    int ret = 0;
    for (int i = 0 ; i < N; ++i) {
        ret += (s[i] == t[i]);
    }

    return ret;
}

int main() {    
    scanf("%d", &N);
    scanf("%s", org);
    for (int i = 0 ; i < N; ++i) s[i] = org[i];
    scanf("%s", t);
    int ans = 0;
    for (char i = 'A'; i <= 'E'; ++i) {
        for (char j = 'A'; j <= 'E'; ++j) {
            change(i, j);
            ans = max(ans, score());
            for (int k = 0 ; k < N; ++k) s[k] = org[k];
        }
    }

    printf("%d\n", ans);
    return 0;
}