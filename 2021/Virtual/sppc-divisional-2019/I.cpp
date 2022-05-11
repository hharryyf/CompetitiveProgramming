#include <bits/stdc++.h>

using namespace std;

map<string, int> cnt;
bool add(string s, int c) {
    if (c > 1) s.pop_back();
    cnt[s] += c;
    return true;
}

bool del(string s, int c) {
    if (c > 1) s.pop_back();
    cnt[s] -= c;
    if (cnt[s] < 0) return false;
    if (cnt[s] == 0) cnt.erase(s);
    return true;
}

char s[111];

int main() {
    int N, M, i;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        int c;
        scanf("%d%s", &c, s);
        add(string(s), c);
    }

    for (i = 1; i <= M; ++i) {
        int c;
        scanf("%d%s", &c, s);
        if (!del(string(s), c)) {
            printf("error\n");
            return 0;
        }
    }

    int sz = cnt.size();
    if (sz == 0) {
        printf("null\n");
    } else if (sz == 1 && cnt.begin()->second == 1) {
        printf("item\n");
    } else {
        printf("items\n");
    }
    return 0;
}