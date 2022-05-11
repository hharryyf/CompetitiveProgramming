#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

char s[MAX_SIZE];
list<char> li;
int N;

int main() {
    int i;
    scanf("%s", s);
    N = strlen(s);
    for (i = 0 ; i < N; ++i) {
        li.push_back(s[i]);
    }

    while (true) {
        if (li.front() != li.back()) {
            printf("0\n");
            return 0;
        }

        char ch = li.front();
        int cnt = 0;
        while (!li.empty()) {
            if (li.front() == ch) {
                li.pop_front();
                cnt++;
            } else if (li.back() == ch) {
                li.pop_back();
                cnt++;
            } else {
                break;
            }
        }

        if (cnt <= 2 && !li.empty()) {
            printf("0\n");
            return 0;
        }

        if (cnt == 1) {
            printf("0\n");
            return 0;
        }

        if (li.empty()) {
            printf("%d\n", cnt + 1);
            return 0;
        }
    }
    return 0;
}