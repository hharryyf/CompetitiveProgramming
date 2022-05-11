#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
map<char, map<int, ll>> mp;
char s[111], t[5];
int d;
int main() {
    while (scanf("%s%s%d", s, t, &d) != EOF) {
        char ch = s[0];
        ll dt = 0;
        for (int i = 2; i < (int) strlen(s); ++i) {
            if (s[i] == '.') break;
            dt = dt * 10;
            dt += (s[i] - '0');
        } 

        mp[ch][dt] += d;
    }

    for (auto ch : mp) {
        printf("%c\n", ch.first);
        for (auto idx : ch.second) {
            if (idx.second != 0)
            printf("%lld\n", idx.second);
        }
    }
    return 0;
}