#include <bits/stdc++.h>
#define SUBMIT
using namespace std;

list<int> judge[11];

int main() {
    #ifdef SUBMIT
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    #endif
    int N, K, curr = 0, i, sm = 0;
    scanf("%d%d", &N, &K);
    for (i = 0; i < N; ++i) {
        int v;
        scanf("%d", &v);
        while (v-- > 0) {
            int h;
            scanf("%d", &h);
            judge[i].push_back(h);
        }
    }

    while (K > 0) {
        if (judge[curr].empty()) {
            sm += 50;
            K--;
        } else {
            if (judge[curr].front() >= sm) {
                sm += judge[curr].front();
                K--;
            }
            judge[curr].pop_front();
        }
        curr = (curr + 1) % N;
    }

    printf("%d\n", sm);
    return 0;
}