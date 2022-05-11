#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

int N, M;

struct Matrix {
    int a[102][102];
    void init() {
        int i, j;
        for (i = 0 ; i < 102; ++i) {
            for (j = 0 ; j < 102; ++j) {
                a[i][j] = 0;
            }
        }
    }
    
    Matrix operator *(Matrix other) const {
        Matrix ret;
        int i, j, k;
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                ret.a[i][j] = inf;
            }
        }

        for (k = 0 ; k < N; ++k) {
            for (i = 0; i < N; ++i) {
                for (j = 0 ; j < N; ++j) {            
                    ret.a[i][j] = min(a[i][k] + other.a[k][j], ret.a[i][j]);
                }
            }
        }

        return ret;
    }

    void print() {
        int i, j;
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
    }
};

bool check1(Matrix m) {
    for (int i = 0; i < N; ++i) {
        if (m.a[0][i] <= M) return true;
    }
    return false;
}

bool check(Matrix m1, Matrix m2) {
    Matrix ret;
    ret = m1 * m2;
    for (int i = 0; i < N; ++i) {
        if (ret.a[0][i] <= M) return true;
    }
    return false;
}

Matrix pw[31];
Matrix curr;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            scanf("%d", &pw[0].a[i][j]);
        }
    }

    for (i = 1; i < 31; ++i) {
        pw[i] = pw[i-1] * pw[i-1];
    }

    //pw[2].print();
    //curr.init();
    int ans = 0;
    for (i = 30; i >= 0; --i) {
        if (ans == 0 && check1(pw[i])) {
            ans = ans + (1 << i);
            curr = pw[i];
        }
        
        if (ans != 0 && check(curr, pw[i])) {
            ans = ans + (1 << i);
            curr = curr * pw[i];
        }
    }

    //curr.print();

    printf("%d\n", ans);
    return 0;
}