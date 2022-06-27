#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;

bool divi(int a, int b) {
    if (b == 0) return false;
    return a % b == 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, W, L;
        set<int> ans;
        scanf("%d%d", &W, &L);
        ans.insert(1);
        // first type
        if (divi(W, 2) && divi(L - 1, 2)) {
            ans.insert(2);
        }

        // second type
        if (divi(L, 2) && divi(W - 1, 2)) {
            ans.insert(2);
        }
        // third type
        for (i = 1; i <= sqrt(max(W - 2, L)); ++i) {
            if (divi(W - 2, i) && divi(L, i)) {
                ans.insert(i);
            }

            if (divi(W - 2, (W - 2) / i) && divi(L, (W - 2) / i)) {
                ans.insert((W - 2) / i);
            }

            if (divi(W - 2, L / i) && divi(L, L / i)) {
                ans.insert(L / i);
            }
            
        }

        // fourth type
        for (i = 1; i <= sqrt(max(L - 2, W)); ++i) {
            if (divi(L - 2, i) && divi(W, i)) {
                ans.insert(i);
            }

            if (divi(L - 2, (L - 2) / i) && divi(W, (L - 2) / i)) {
                ans.insert((L - 2) / i);
            }

            if (divi(L - 2, W / i) && divi(W, W / i)) {
                ans.insert(W / i);
            }
        }

        // fifth type
        for (i = 1; i <= sqrt(max(W - 1, L - 1)); ++i) {
            if (divi(W - 1, i) && divi(L - 1, i)) {
                ans.insert(i);
                
            }

            if (divi(W - 1, (W - 1) / i) && divi(L - 1, (W - 1) / i)) {
                ans.insert((W - 1) / i);
            }

            if (divi(W - 1, (L - 1) / i) && divi(L - 1, (L - 1) / i)) {
                ans.insert((L - 1) / i);
            }
        }
        printf("%d", (int) ans.size());
        for (auto v : ans) {
            printf(" %d", v);
        }
        printf("\n");
    }
    return 0;
}