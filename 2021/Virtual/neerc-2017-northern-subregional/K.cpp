#include <bits/stdc++.h>

using namespace std;
int N, M, C;

#define FILEIO

void openfile(string filename="kotlin") {
    #ifdef FILEIO
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
    #endif
}

void build(int d) {
    int i, j, r = d * 2, c = (C / d) * 2;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            if (i <= r && j <= c) {
                if (i % 2 == 1 && j % 2 == 1) {
                    printf(".");
                } else {
                    printf("#");
                }
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

int main() {
    int i;
    openfile();
    scanf("%d%d%d", &N, &M, &C);
    if (C > N * M) {
        printf("Impossible\n");
        return 0;
    }

    for (i = 1; i <= N; ++i) {
        if (C % i == 0 && i * 2 - 1 <= N && (C / i) * 2 - 1 <= M) {
            build(i);
            return 0;
        }
    }

    printf("Impossible\n");
    return 0;
}