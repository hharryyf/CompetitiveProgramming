#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char s[MAX_SIZE];

bool check(string ss, int U, int D, int R, int L, int X, int Y) {
    int x = 0, y = 0;
    if (x == X && y == Y) return false;
    string res = "";
    for (int i = 0; i < 4; ++i) {
        if (ss[i] == 'U') {
            while (U-- > 0) {
                res.push_back(ss[i]);
                y++;
                if (x == X && y == Y) return false;
            }
        } else if (ss[i] == 'D') {
            while (D-- > 0) {
                res.push_back(ss[i]);
                y--;
                if (x == X && y == Y) return false;
            }
        } else if (ss[i] == 'R') {
            while (R-- > 0) {
                res.push_back(ss[i]);
                x++;
                if (x == X && y == Y) return false;
            }
        } else {
            while (L-- > 0) {
                res.push_back(ss[i]);
                x--;
                if (x == X && y == Y) return false;
            }
        }
    }

    printf("%s\n", res.c_str());
    return true;
}

int main() {
    int T, N;
    scanf("%d", &T);
    while (T-- > 0) {
        int X, Y, i, U=0, D=0, L=0, R=0;
        scanf("%d%d", &X, &Y);
        scanf("%s", s);
        N = strlen(s);
        for (i = 0 ; i < N; ++i) {
            if (s[i] == 'U') ++U;
            if (s[i] == 'R') ++R;
            if (s[i] == 'D') ++D;
            if (s[i] == 'L') ++L;
        }

        if (U - D == Y && R - L == X) {
            printf("Impossible\n");
            continue;
        }

        vector<int> ch;
        string ss = "URDL";
        for (i = 0 ; i < 4; ++i) ch.push_back(i);
        int ok = 0;
        do {
            string st = string(ss);
            for (i = 0 ; i < 4; ++i) {
                st[i] = ss[ch[i]];
            }

            if (check(st, U, D, R, L, X, Y)) {
                ok = 1;
                break;
            }
        } while (next_permutation(ch.begin(), ch.end()));
        if (!ok) printf("Impossible\n");
    }
    return 0;
}


/*

5
1 1
RURULLD
0 5
UUU
0 3
UUU
0 2
UUU
0 0
UUU

*/