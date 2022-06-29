#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
ll a[MAX_SIZE];
ll mv[MAX_SIZE][2];
int N;

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%lld", &a[i]);
            mv[i][0] = mv[i][1] = 0;
        }

        /*
            Move(1, r) = a[1]
            Move(2, l) = Move(1, r)
            Move(2, r) - Move(2, l) = a[2] 
            Move(3, l) = Move(2, r)
            Move(3, r) - Move(3, l) = a[3]
        */
        mv[1][1] = a[1];
        for (i = 2; i <= N; ++i) {
            mv[i][0] = mv[i-1][1];
            mv[i][1] = mv[i][0] + a[i];
        }

        bool bad = false;
        for (i = 1; i <= N; ++i) {
            if (mv[i][0] < 0 || mv[i][1] < 0 || mv[N][1] != 0) {
                bad = true;
            }
        }

        for (i = 2; i <= N; ++i) {
            if (mv[i][0] == 0) {
                if (mv[i-1][1] != 0) {
                    bad = true;
                    break;
                }

                for (int j = i; j <= N; ++j) {
                    if (mv[j][1] != 0 || mv[j][0] != 0) {
                        bad = true;
                    }
                }
                break;
            }
        }

        for (i = 1; i <= N; ++i) {
            if (mv[i][1] == 0) {
                for (int j = i + 1; j <= N; ++j) {
                    if (mv[j][0] != 0 || mv[j][1] != 0) {
                        bad = true;
                    }
                }
                break;
            }
        }

        printf("%s\n", bad ? "No" : "Yes");
    }
    return 0;
}