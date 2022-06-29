#pragma GCC optimize(3)
#include <bits/stdc++.h>

#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;


char s[MAX_SIZE];
int k1, k2, k3, k4;
int x1[MAX_SIZE], x2[MAX_SIZE], x3[MAX_SIZE], x4[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int W, H;
        scanf("%d%d", &W, &H);
        scanf("%d", &k1);
        for (int i = 0 ; i < k1; ++i) {
            scanf("%d", &x1[i]);
        }
        scanf("%d", &k2);
        for (int i = 0 ; i < k2; ++i) {
            scanf("%d", &x2[i]);
        }
        scanf("%d", &k3);
        for (int i = 0 ; i < k3; ++i) {
            scanf("%d", &x3[i]);
        }
        scanf("%d", &k4);
        for (int i = 0 ; i < k4; ++i) {
            scanf("%d", &x4[i]);
        }
        
        ll ans1 =  max(1ll * (x4[k4 - 1] - x4[0]) * W, 1ll * (x3[k3 - 1] - x3[0]) * W);
        ll ans2 = max(1ll * (x1[k1 - 1] - x1[0]) * H, 1ll * (x2[k2 - 1] - x2[0]) * H);
    
        printf("%lld\n", max(ans1, ans2));
    }
    return 0;
}