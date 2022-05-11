#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

char team[MAX_SIZE][3][MAX_SIZE];
bool sel[MAX_SIZE];
map<string, int> unicount;
int N;

void ruleA(string s) {
    int i;
    int cnt = 0;
    for (i = 1; i <= N && cnt < 2; ++i) {
        if (strcmp(team[i][1], s.c_str()) == 0 && unicount[team[i][2]] == 0) {
            sel[i] = true;
            unicount[team[i][2]]++;
            cnt++;
        }
    }
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s%s%s", team[i][0], team[i][1], team[i][2]);
    }

    ruleA("Eastern");
    ruleA("Central");
    ruleA("Western");

    int cnt = 6;
    for (i = 1; i <= N && cnt < 12; ++i) {
        if (!sel[i] && unicount[team[i][2]] < 2) {
            sel[i] = true;
            unicount[team[i][2]]++;
            cnt++;
        }
    }    

    for (i = 1; i <= N; ++i) {
        if (sel[i]) {
            printf("%s\n", team[i][0]);
        }
    }
    return 0;
}