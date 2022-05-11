#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int main() {
    int T, t;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        ll x1, x2, x3, x4, x5;
        scanf("%lld%lld%lld%lld%lld", &x1, &x2, &x3, &x4, &x5);
        int N;
        ll ret = 0;
        scanf("%d", &N);
        while (N-- > 0) {
            int id;
            scanf("%d", &id);
            if (id <= 48) {
                ret += x1;
            } else if (id <= 56) {
                ret += x2;
            } else if (id <= 60) {
                ret += x3;
            } else if (id <= 62) {
                ret += x4;
            } else {
                ret += x5;
            }
        }

        
            printf("%lld\n", ret * 10000);
    }
    return 0;
}