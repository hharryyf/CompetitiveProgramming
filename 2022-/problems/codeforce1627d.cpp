#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
typedef long long ll;
#define MAX_SIZE 1000011
using namespace std;

vector<int> g[MAX_SIZE];
int visited[MAX_SIZE];
int a[MAX_SIZE];

int main() {
    int i, j, N;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        visited[a[i]] = 1;
    }

    for (i = 1; i <= 1000000; ++i) {
        for (j = 1; j * i <= 1000000; ++j) {
            if (visited[j * i]) {
                g[i].push_back(j * i);
            }
        }
    }

    int cnt = 0;
    for (i = 1; i <= 1000000; ++i) {
        int ret = 0;
        if (g[i].empty()) continue;
        for (auto v : g[i]) {
            ret = __gcd(ret, v);
        }

        if (ret == i) {
            cnt++;
            debug("%d\n", i);
        }
    }

    printf("%d\n", cnt - N);
    return 0;
}