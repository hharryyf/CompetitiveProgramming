#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int n;
        ll B, x, y;
        cin >> n >> B >> x >> y;
        ll curr = 0, ans = 0;
        for (int i = 1 ; i <= n; ++i) {
            if (curr + x <= B) {
                curr = curr + x;
            } else {
                curr = curr - y;
            }

            ans += curr;
        }

        cout << ans << endl;
    }
    return 0;
}