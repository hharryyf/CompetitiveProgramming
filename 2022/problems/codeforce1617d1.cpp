#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
using namespace std;

int query(int i, int j, int k) {
    int ret;
    cout << "? " << i << " " << j << " " << k << endl;
    cin >> ret;
    if (ret == -1) exit(0);
    return ret ^ 1; 
}

int main() {
    int T, N, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        vector<int> ok(N-1);
        for (i = 1; i <= N - 2; ++i) {
            ok[i] = query(i, i + 1, i + 2);
        }

        int zero = -1, one = -1;
        for (i = 1; i <= N - 3; ++i) {
            if (ok[i] && !ok[i+1]) {
                one = i, zero = i + 3;
            } else if (!ok[i] && ok[i+1]) {
                one = i + 3, zero = i;
            }
        }

        vector<int> ans = vector<int>(N + 1, -1);
        ans[one] = 1;
        ans[zero] = 0;
        int cnt = 0;
        for (i = 1; i <= N; ++i) {
            if (ans[i] == -1) {
                if (query(one, zero, i)) {
                    ans[i] = 1;
                } else {
                    ans[i] = 0;
                }
            }

            if (ans[i] == 1) cnt++;
        }
        cout << "! " << cnt;
        for (i = 1; i <= N; ++i) {
            if (ans[i] == 1) {
                cout << " " << i;
            }
        }
        cout << endl;
    }
    return 0;
}