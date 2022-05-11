#include <bits/stdc++.h>
#define MAX_SIZE 5011
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll dp[MAX_SIZE][MAX_SIZE];
ll pre[MAX_SIZE][MAX_SIZE];
ll pk[MAX_SIZE][MAX_SIZE];
ll add(ll u, ll v) {
    ll ret = (u + v) % mod;
    if (ret < 0) ret += mod;
    return ret;
}

ll mul(ll u, ll v) {
    return (u * v) % mod;
}

int main() {
    int S, B, i, j;
    scanf("%d%d", &B, &S);

    for (i = 1; i <= B; ++i) {
        dp[i][i] = 1;
    }
    pk[1][1] = 1;
    pre[1][1] = 1;

    for (i = 2; i <= S; ++i) {
        for (j = 1; j <= B && j < i; ++j) {
            dp[i][j] = add(dp[i][j], mul(pre[i-j][min(j, i - j)], 1 + j));
            dp[i][j] = add(dp[i][j], -pk[i-j][min(j, i - j)]); 
        }

        for (j = 1; j <= i && j <= B; ++j) {
            pre[i][j] = add(pre[i][j-1], dp[i][j]);
            pk[i][j] = add(pk[i][j-1], mul(dp[i][j], j)); 
        }
    }

    cout << add(dp[S][B], mod) << endl;
    return 0;
}