#include <bits/stdc++.h>
#define MAX_SIZE 1027
using namespace std;

char s[MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
int table[10][MAX_SIZE];
int logs[MAX_SIZE];
int N, M;

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int RMQ(int l, int r) {
    if (l > r) return 4 * MAX_SIZE;
    int len = r - l + 1;
    return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
}

void build(int dim) {
    int i, j;
    for (i = 1; i <= N; i++) {
        table[0][i] = a[i][dim];
    }
    
    for (i = 1; i <= 9; i++) {
        int prel = (1 << (i - 1));
        for (j = 1; j <= N; j++) {
            if (j + prel <= N) {
                table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
}

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%s", s + 1);
        for (j = 1; j <= M; ++j) {
            if (j == 1 || s[j] != s[j-1]) {
                a[i][j] = 1;
            } else {
                a[i][j] = a[i][j-1] + 1;
            }
        }
    }

    precompute();
    int ans = 0;
    for (i = 1; i <= M; ++i) {
        build(i);
        for (j = 1; j <= N; ++j) {
            int low = 1, high = j, L = j, R = j;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (RMQ(mid, j) == a[j][i]) {
                    L = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            
            low = j, high = N;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (RMQ(j, mid) == a[j][i]) {
                    R = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            int len = min(R - L + 1, a[j][i]);
            ans = max(ans, len * len);
        }
    }

    printf("%d\n", ans);
    return 0;
}