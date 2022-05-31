#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 2011
using namespace std;
typedef long long ll;
char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        vector<int> base;
        vector<ll> ret; 
        int N, K, i, j;
        ll X;
        scanf("%d%d%lld", &N, &K, &X);
        X--;
        scanf("%s", s + 1);
        int cnt = 0;
        for (i = 1; i <= N; ++i) {
            if (s[i] == 'a' && cnt != 0) {
                base.push_back(cnt * K);
                cnt = 0;
            }

            if (s[i] == '*') cnt++;
        }

        if (cnt != 0) {
            base.push_back(cnt * K);
        }

        i = (int) base.size() - 1;
        while (X > 0) {
            ret.push_back(X % (base[i] + 1));
            X = X / (base[i] + 1);
            i--;
        }

        while (ret.size() < base.size()) {
            ret.push_back(0);
        }

        reverse(ret.begin(), ret.end());

        for (auto b : ret) {
            debug("%d ", b);
        }
        debug("\n");

        for (i = 1, j = 0; i <= N; ++i) {
            if (s[i] == 'a') {
                printf("%c", s[i]);
            } else if (s[i] == '*' && (i == 1 || s[i-1] == 'a')) {
                for (int k = 0 ; k < ret[j]; ++k) {
                    printf("%c", 'b');
                }
                ++j;
            }
        }
        printf("\n");
    }
    return 0;
}