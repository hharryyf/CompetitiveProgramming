#include <bits/stdc++.h>
#define MAX_SIZE 4911
using namespace std;

int state[MAX_SIZE];
// each switch, which light it can control
vector<int> g[MAX_SIZE];
int light[MAX_SIZE][3];
char s[8];
int N, M;

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        for (i = 1; i <= M; ++i) {
            g[i].clear();
        }
        
        for (i = 1; i <= M; ++i) {
            state[i] = -1;
        }

        for (i = 1; i <= N; ++i) {
            for (j = 0; j < 3; ++j) {
                scanf("%s", s);
                if (s[0] == '+') {
                    light[i][j] = atoi(s+1);
                } else {
                    light[i][j] = atoi(s);
                }

                g[abs(light[i][j])].push_back(i);
            }
        }

        for (int k = 1; k <= 10000; ++k) {
            int delta = 0;
            int idx = -1;
            for (i = 1; i <= M; ++i) {
                int tmp = 0;
                // switch the state of switch i
                state[i] *= -1;
                for (auto lit : g[i]) {
                    // lit is the id of the light controlled by switch i
                    state[i] *= -1;
                    int pre = 0, curr = 0;
                    //printf("check pre\n");
                    for (j = 0 ; j < 3; ++j) {
                        //printf("%d--%d\n", state[light[abs(lit)][j]], light[abs(lit)][j]);
                        if (state[abs(light[abs(lit)][j])] * light[abs(lit)][j] > 0) {
                            pre = 1;
                            break;
                        }
                    }
                    state[i] *= -1;
                    //printf("check after\n");
                    for (j = 0 ; j < 3; ++j) {
                        //printf("%d--%d\n", state[light[abs(lit)][j]], light[abs(lit)][j]);
                        if (state[abs(light[abs(lit)][j])] * light[abs(lit)][j] > 0) {
                            curr = 1;
                            break;
                        }
                    }

                    tmp += curr - pre;
                    //printf("after switch %d, pre=%d, curr=%d\n", i, pre, curr);
                }

                if (delta < tmp) {
                    delta = tmp;
                    idx = i;
                }

                //printf("iteration %d, switch=%d, delta=%d\n", k, i, tmp);    
                state[i] *= -1;
            }

            if (delta == 0) {
                break;
            }

            
            state[idx] *= -1;
        }

        for (i = 1; i <= M; ++i) {
            if (state[i] == -1) {
                printf("-");
            } else {
                printf("+");
            }
        }
        printf("\n");
    }
    return 0;
}