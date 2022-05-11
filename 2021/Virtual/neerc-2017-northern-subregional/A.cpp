#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int dp[MAX_SIZE];
int digit[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};


void openfile(string filename="auxiliary") {
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
}

int main() {
    dp[0] = 0;
    dp[1] = -1000000000;
    int i, n;
    openfile();
    scanf("%d", &n);
    for (i = 2; i <= n; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i >= digit[j]) {
                dp[i] = max(dp[i], dp[i - digit[j]] + j);
            }
        }
    }

    printf("%d\n", dp[n]);
    return 0;
}