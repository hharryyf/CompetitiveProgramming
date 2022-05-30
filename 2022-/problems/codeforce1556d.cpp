#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;
// 1,6,4,2,3,5,4
int vor[MAX_SIZE], vand[MAX_SIZE];
int x[MAX_SIZE];

int solve(int and23, int or23, int and12, int or12, int and13, int or13) {
    debug("%d %d %d %d %d %d\n", and23, or23, and12, or12, and13, or13);
    int i;
    int ret = 0;
    for (i = 0 ; i < 31; ++i) {
        if (((or12 >> i) & 1) == 0 || ((or13 >> i) & 1) == 0) {
            debug("digit %d, val=%d, ret = %d\n", i, 1, ret);
            continue;
        }

        if (((and12 >> i) & 1) == 1 || ((and13 >> i) & 1) == 1) {
            ret = ret | (1 << i);
            debug("digit %d, val=%d, ret = %d\n", i, 1, ret);
            continue;
        }

        // or12 = 1, or13 = 1, and12 = 0, and13 = 0
        if (((and23 >> i) & 1) == 1) {
            debug("digit %d, val=%d, ret = %d\n", i, 1, ret);
            continue;
        }

        ret = ret | (1 << i);
        debug("digit %d, val=%d, ret = %d\n", i, 1, ret);
    }

    return ret;
}

int main() {
    int N, K, i;
    scanf("%d%d", &N, &K);
    for (i = 2; i <= N; ++i) {
        cout << "and 1 " << i << endl;
        cin >> vand[i];
        if (vand[i] == -1) {
            return 0;
        }
        cout << "or 1 " << i << endl;
        cin >> vor[i];
        if (vor[i] == -1) {
            return 0;
        }
    }
    cout << "and 2 3" << endl;
    cin >> vand[1];
    if (vand[1] == -1) {
        return 0;
    }
    cout << "or 2 3" << endl;
    cin >> vor[1];
    if (vor[1] == -1) {
        return 0;
    }
    x[1] = solve(vand[1], vor[1], vand[2], vor[2], vand[3], vor[3]);

    for (i = 2; i <= N; ++i) {
        // know x[1], know x[1] | x[i], know x[1] & x[i]
        // get x[i]
        for (int j = 0 ; j < 31; ++j) {
            if (((x[1] >> j) & 1) == 1 && ((vand[i] >> j) & 1) == 1) {
                x[i] |= (1 << j);
            } else if (((x[1] >> j) & 1) == 0 && ((vor[i] >> j) & 1) == 1) {
                x[i] |= (1 << j);
            }
        }
    }

    sort(x + 1, x + 1 + N);
    cout << "finish " << x[K] << endl;
    //fflush(stdout);
    for (i = 1; i <= N; ++i) {
        debug("%d ", x[i]);
    }
    return 0;
}