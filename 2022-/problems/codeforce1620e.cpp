#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 500011

pair<int, int> a[MAX_SIZE];
int t[MAX_SIZE];
map<pair<int, int>, pair<int, int>> f;

pair<int, int> find(pair<int, int> x) {
    if (f.find(x) == f.end()) return x;
    return f[x] = find(f[x]);
}

int main() {
    int Q, K = 0, i;
    scanf("%d", &Q);
    while (Q-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int x;
            scanf("%d", &x);
            a[++K] = {x, t[x]};
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == y) continue;
            pair<int, int> fx = find(make_pair(x, t[x]));
            pair<int, int> fy = find(make_pair(y, t[y]));
            f[fx] = fy; 
            t[x]++;
        }
    }    

    for (i = 1; i <= K; ++i) {
        auto x = find(a[i]);
        printf("%d ", x.first);
    }
    printf("\n");
    return 0;
}