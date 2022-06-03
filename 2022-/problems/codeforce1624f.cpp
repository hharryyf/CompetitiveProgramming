#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#define D
#define MAX_SIZE 262192
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
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
typedef long long ll;
int N;

int query(int x) {
    cout << "+ " << x << endl;
    cin >> x;
    if (x == -1) exit(0);
    return x;
}

int main() {
    cin >> N;
    int i, j, l = 1, r = N - 1, inc = 0;
    while (r - l >= 1) {
        int bestpivot = -1, diff = N + 1;
        for (i = 1; i < N; ++i) {
            map<int, int> cnt;
            for (j = l; j <= r; ++j) {
                cnt[(j + inc + i) / N]++;
            }

            int elim = -1;
            if ((int) cnt.size() == 1) {
                elim = cnt.begin()->second;
                if (elim < diff) {
                    diff = elim;
                    bestpivot = i;
                }
            } else {
                elim = cnt.begin()->second - cnt.rbegin()->second;
                if (elim < 0) elim *= -1;
                if (elim < diff) {
                    diff = elim;
                    bestpivot = i;
                }
            }
        }

        inc += bestpivot;
        bestpivot = query(bestpivot);
        debug("best pivot = %d\n", bestpivot);
        vector<int> ok;
        for (i = l; i <= r; ++i) {
            if ((i + inc) / N == bestpivot) {
                ok.push_back(i);
            }
        }

        debug("size=%d\n", (int) ok.size());

        l = ok.front(), r = ok.back();
        debug("ok range %d %d\n", l, r);
    }

    cout << "! " << l + inc << endl;
    return 0;
}