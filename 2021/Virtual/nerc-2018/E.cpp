#include <bits/stdc++.h>

using namespace std;

vector<pair<char, int>> ret;
int vis[9][9];
pair<char, int> mp(int x, int y) {
    return {x + 'a' - 1, y};
}

void putval(int x, int y) {
    ret.push_back(mp(x, y));
    vis[x][y] = 1;
}

bool solve(int step) {
    int orstep = step, i;
    ret.clear();
    

    memset(vis, 0, sizeof(vis));

    putval(1, 1);            
    int x = 1, y = 1;

    while (step > 0) {
        if (x == 8) {
            if (step == 1) {
                putval(8, 8);
                break;
            } else {
                for (i = 1; i <= 8; ++i) {
                    if (!vis[8][i]) {
                        putval(8, i);
                        break;
                    }
                }
            }
        } else {
            if (step == 2) {
                putval(8, y);
                putval(8, 8);
                break;
            } else {
                if ((int) ret.size() % 8 == 0) {
                    putval(++x, y);
                } else {
                    if (step >= 4 && !vis[x][8]) {
                        putval(x, 8);
                        y = 8;                        
                    } else {
                        for (i = 1; i <= 8; ++i) {
                            if (!vis[x][i]) {
                                putval(x, i);
                                y = i;
                                break;
                            }
                        }        
                    }
                }
            }
        }

        step--;
    }
    bool ok = true;
    if ((int) ret.size() != orstep + 1) {
        ok = false;
        printf("step %d is invalid\n", orstep);
    }
    set<pair<char, int>> st;
    printf("%c%d", ret[0].first, ret[0].second);
    st.insert(ret[0]);
    for (i = 1 ; i < (int) ret.size(); ++i) {
        if (ret[i].first != ret[i-1].first && ret[i].second != ret[i-1].second) {
            ok = false;
            printf("step %d invalid\n", orstep);
        }

        if (st.find(ret[i]) != st.end()) {
            ok = false;
            printf("duplicate step %d\n", orstep);
        }
        printf(" %c%d", ret[i].first, ret[i].second);
        st.insert(ret[i]);
    } 

    printf("\n");
    return ok;
}

int main() {
    /*int T;
    for (T = 2; T <= 63; ++T) {
        if (!solve(T)) {
            printf("wrong!\n");
            exit(0);
        }
    }*/

    int N;
    scanf("%d", &N);
    solve(N);
    return 0;
}