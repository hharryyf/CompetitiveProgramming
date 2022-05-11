#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
char s[MAX_SIZE];
int N, M;

int main() {
    int i, cnt = 0;
    ll ans = 0;
    scanf("%s", s);
    M = strlen(s);
    scanf("%d", &N);
    for (i = 0 ; i < M; ++i) {
        cnt += s[i] == 'E';
    }

    if (cnt == 0) {
        printf("0\n");
        return 0;
    }

    ans = 1ll * M * N;
    //cout << ans << endl;
    vector<int> pos;
    for (i = 0 ; i < M; ++i) {
        if (s[i] == 'E') {
            pos.push_back(i);
        }
    }

    for (i = 1; i < (int) pos.size(); ++i) {
        int B = min(pos[i] - pos[i-1] - 1, N), len = pos[i] - pos[i-1] - 1;
        //cout << len << " " << B << endl;
        ans = ans - 1ll * (len + len - B + 1) * B / 2;
    }
    //cout << ans << endl;
    int len = M - pos.back() + pos.front() - 1;
    int B = min(len, N);
    //cout << len << " " << B << endl;
    ans = ans - 1ll * (len + len - B + 1) * B / 2;
    printf("%lld\n", ans);
    return 0;
}