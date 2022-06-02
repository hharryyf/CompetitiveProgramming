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

// #define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif

int query(int i, int j, int k) {
    int ret;
    cout << "? " << i << " " << j << " " << k << endl;
    cin >> ret;
    if (ret == -1) exit(0);
    return ret ^ 1; 
}

int main() {
    int T;
    cin >> T;
    while (T-- > 0) {
        int N, i;
        cin >> N;
        vector<int> res = vector<int>(N + 1, -1);
        vector<int> ans = vector<int>(N + 1, -1);
        int zero = -1, one = -1;
        // #query = N / 3
        for (i = 1; i <= N - 2; i = i + 3) {
            int ret = query(i, i + 1, i + 2);
            if (zero == -1 && ret == 0) zero = i;
            if (one == -1 && ret == 1) one = i;
            res[i] = ret;
        }

        // # query += 2
        int zeropos = -1, onepos = -1;
        vector<int> imp = {zero, zero + 1, zero + 2, one, one + 1, one + 2};
        vector<int> ok = vector<int>(4, 0);
        debug("critical %d %d %d %d %d %d\n", zero, zero + 1, zero + 2, one, one + 1, one + 2);
        for (i = 0; i < 4; ++i) {
            if (i == 0) {
                ok[i] = 0;
            } else if (i == 3) {
                ok[i] = 1;
            } else {
                ok[i] = query(imp[i], imp[i+1], imp[i+2]);
            }
        }

        for (i = 0 ; i < 3; ++i) {
            if (ok[i] == 0 && ok[i+1] == 1) {
                zeropos = imp[i], onepos = imp[i + 3];    
                break;
            } else if (ok[i] == 1 && ok[i+1] == 0) {
                zeropos = imp[i + 3], onepos = imp[i];
                break;
            }
        }

        ans[zeropos] = 0;
        ans[onepos] = 1;
        // # query += 4
        for (i = 0; i < 6; ++i) {
            if (imp[i] == zeropos || imp[i] == onepos) continue;
            ans[imp[i]] = query(imp[i], zeropos, onepos);
        }

        for (i = 0 ; i < 6; ++i) {
            debug("ans[imp[%d]] = %d\n", i, ans[imp[i]]);
        }
        // # query += 2 * N / 3
        for (i = 1; i <= N - 2; i = i + 3) {
            if (i == zero || i == one) continue;
            int fi = -1, se = -1;
            if (res[i] == 0) {
                fi = query(i, i + 1, onepos);
                se = query(i + 1, i + 2, onepos);
                if (fi == 1 && se == 1) {
                    ans[i] = 0, ans[i + 2] = 0, ans[i + 1] = 1;
                } else if (fi == 1 && se == 0) {
                    ans[i] = 1, ans[i + 1] = 0, ans[i + 2] = 0;
                } else if (fi == 0 && se == 1) {
                    ans[i] = 0, ans[i + 1] = 0, ans[i + 2] = 1;
                } else {
                    ans[i] = 0, ans[i + 1] = 0, ans[i + 2] = 0;
                }
            } else {
                fi = query(i, i + 1, zeropos);
                se = query(i + 1, i + 2, zeropos);
                if (fi == 1 && se == 1) {
                    ans[i] = 1, ans[i + 2] = 1, ans[i + 1] = 1;
                } else if (fi == 1 && se == 0) {
                    ans[i] = 1, ans[i + 1] = 1, ans[i + 2] = 0;
                } else if (fi == 0 && se == 1) {
                    ans[i] = 0, ans[i + 1] = 1, ans[i + 2] = 1;
                } else {
                    ans[i] = 1, ans[i + 1] = 0, ans[i + 2] = 1;
                }
            }
        }

        int cnt = 0;
        for (i = 1; i <= N; ++i) {
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