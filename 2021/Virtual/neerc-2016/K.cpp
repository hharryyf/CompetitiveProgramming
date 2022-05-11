#include <bits/stdc++.h>
#define MAX_SIZE 1011
#define SUBMIT
using namespace std;


int N1, M1, N2, M2, N3, M3;
char s[MAX_SIZE][MAX_SIZE];

void openfile() {
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
}

int main() {
    #ifdef SUBMIT
    openfile();
    #endif
    int i, j;
    set<pair<int, int>> s1, s2, s3;
    set<pair<int, int>> ret;
    scanf("%d%d", &N1, &M1);
    for (i = 1; i <= N1; ++i) {
        scanf("%s", s[i] + 1);
        for (j = 1; j <= M1; ++j) {
            if (s[i][j] == '*') {
                s1.emplace(i, j);
            }
        }
    }

    scanf("%d%d", &N2, &M2);
    for (i = 1; i <= N2; ++i) {
        scanf("%s", s[i] + 1);
        for (j = 1; j <= M2; ++j) {
            if (s[i][j] == '*') {
                s2.emplace(i, j);
            }
        }
    }

    scanf("%d%d", &N3, &M3);
    for (i = 1; i <= N3; ++i) {
        scanf("%s", s[i] + 1);
        for (j = 1; j <= M3; ++j) {
            if (s[i][j] == '*') {
                s3.emplace(i, j);
            }
        }
    }

    // check merge s2 to s1 and res match s3
    auto q = *s2.begin(), p = *s1.begin();
    int dx = p.first - q.first, dy = p.second - q.second;   
    for (auto pp : s1) {
        ret.insert(pp);
    }

    for (auto pp : s2) {
        if (ret.find(make_pair(pp.first + dx, pp.second + dy)) != ret.end()) {
            ret.erase(make_pair(pp.first + dx, pp.second + dy));
        } else {
            ret.insert(make_pair(pp.first + dx, pp.second + dy));
        }
    }

    if (ret.size() == s3.size()) {
        bool flag = true;
        p = *ret.begin(), q = *s3.begin();
        dx = p.first - q.first, dy = p.second - q.second;
        for (auto pp : s3) {
            if (ret.find(make_pair(pp.first + dx, pp.second + dy)) == ret.end()) {
                flag = false;
                break;
            }
        }

        if (flag) {
            #ifndef SUBMIT
            printf("Case 1\n");
            #endif
            printf("YES\n");
            q = *s2.begin(), p = *s1.begin();
            printf("%d %d\n", p.second - q.second, p.first - q.first);
            return 0;
        }
    }
    ret.clear();
    // check merge s2 and s3 and res match s1
    q = *s3.begin(), p = *s2.begin();
    dx = p.first - q.first, dy = p.second - q.second;   
    for (auto pp : s2) {
        ret.insert(pp);
    }

    for (auto pp : s3) {
        if (ret.find(make_pair(pp.first + dx, pp.second + dy)) != ret.end()) {
            ret.erase(make_pair(pp.first + dx, pp.second + dy));
        } else {
            ret.insert(make_pair(pp.first + dx, pp.second + dy));
        }
    }
    /*
    for (auto pp : s1) {
        printf("%d %d\n", pp.first, pp.second);
    }*/
    if (ret.size() == s1.size()) {
        bool flag = true;
        q = *ret.begin(), p = *s1.begin();
        dx = p.first - q.first, dy = p.second - q.second;
        //cout << dx << " " << dy << endl;
        for (auto pp : ret) {
            if (s1.find(make_pair(pp.first + dx, pp.second + dy)) == s1.end()) {
                flag = false;
                break;
            }
        }

        if (flag) {
            #ifndef SUBMIT
            printf("Case 2\n");
            #endif
            printf("YES\n");
            printf("%d %d\n", dy, dx);
            return 0;
        }
    }
    ret.clear();      
    // check merge s1 and s3 and res match s2
    q = *s3.begin(), p = *s1.begin();
    dx = p.first - q.first, dy = p.second - q.second;   
    for (auto pp : s1) {
        ret.insert(pp);
    }

    for (auto pp : s3) {
        if (ret.find(make_pair(pp.first + dx, pp.second + dy)) != ret.end()) {
            ret.erase(make_pair(pp.first + dx, pp.second + dy));
        } else {
            ret.insert(make_pair(pp.first + dx, pp.second + dy));
        }
    }

    if (ret.size() == s2.size()) {
        bool flag = true;
        q = *s2.begin(), p = *ret.begin();
        dx = p.first - q.first, dy = p.second - q.second;
        for (auto pp : s2) {
            if (ret.find(make_pair(pp.first + dx, pp.second + dy)) == ret.end()) {
                flag = false;
                break;
            }
        }

        if (flag) {
            #ifndef SUBMIT
            printf("Case 3\n");
            #endif
            printf("YES\n");
            printf("%d %d\n", dy, dx);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}