#pragma GCC optimize(3)
#pragma GCC optimize(2)
#define D
#define MAX_SIZE 104
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
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
#include <bitset>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

int N, Q;

int main() {
    int i, j;
    scanf("%d", &Q);
    while (Q-- > 0) {
        vector<int> disc, tmp;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            int v;
            scanf("%d", &v);
            tmp.push_back(v);
        }

        sort(tmp.begin(), tmp.end());

        for (i = 0 ; i < (int) tmp.size(); ++i) {
            if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
        }

        int ans = 0;
        for (i = 0 ; i < (int) disc.size(); ++i) {
            ans = max(ans, disc[i]);
            j = i - 1;
            while (j >= 0) {
                if (disc[i] % disc[j] != 0) {
                    ans = max(ans, disc[i] + disc[j]);
                    int k = j - 1;
                    while (k >= 0) {
                        if (disc[j] % disc[k] != 0 && disc[i] % disc[k] != 0) {
                            ans = max(ans, disc[i] + disc[j] + disc[k]);
                            break;
                        }
                        --k;
                    }
                    break;
                }
                --j;
            }
            
        }

        printf("%d\n", ans);
    }
    return 0;
}