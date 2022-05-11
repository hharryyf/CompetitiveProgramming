#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

const int mod = 1e9 + 7;
char s[MAX_SIZE];
typedef long long ll;
// dp[i][0] 101010
// dp[i][1] 1010101
ll dp[MAX_SIZE][2];


int main() {
    scanf("%s", s + 1);
    int len = strlen(s + 1), i;
    ll cnt = 0;
    for (i = 1; i <= len; ++i) {
        if (s[i] == '0') {
            dp[i][0] = dp[i-1][0] + dp[i-1][1] + cnt;
            dp[i][0] %= mod;
            dp[i][1] = dp[i-1][1];
        } else {
            dp[i][1] = dp[i-1][1] + dp[i-1][0];
            dp[i][1] %= mod;
            dp[i][0] = dp[i-1][0];
            cnt++;
        }

        // printf("%lld %lld\n", dp[i][0], dp[i][1]);
    }
    
    printf("%lld\n", dp[len][1]);
    return 0;
}