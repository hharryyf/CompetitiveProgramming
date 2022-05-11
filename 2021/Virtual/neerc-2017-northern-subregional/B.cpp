#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;
#define FILEIO

void openfile(string filename="boolean") {
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
}

char s[MAX_SIZE];

int main() {
    ll ret = 1;
    int flag = 1;
    set<char> st;
    set<char> neg, pos;
    #ifdef FILEIO
    openfile();
    #endif
    scanf("%s", s);
    int len = strlen(s), i;
    for (i = 0 ; i < len; ++i) {
        if (s[i] != '|' && s[i] != '~') {
            st.insert(s[i]);
            if (i != 0 && s[i-1] == '~') {
                neg.insert(s[i]);
            }

            if (i == 0 || s[i-1] != '~') {
                pos.insert(s[i]);
            }   
        }
    } 

    for (auto ch : neg) {
        if (pos.find(ch) != pos.end()) flag = 0;
    }

    for (i = 0 ; i < (int) st.size(); ++i) ret = ret * 2;
    printf("%lld\n", ret - flag);
    return 0;
}