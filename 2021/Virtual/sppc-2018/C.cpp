#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

struct jobs {
    int t, prereq;
    bool operator < (jobs other) const {
        if (prereq != other.prereq) return prereq < other.prereq;
        return t < other.t;
    }
};

jobs jb[MAX_SIZE];
int N, K;

int main() {
    int i = 0, pos = 1;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &jb[i].t, &jb[i].prereq);
    }

    sort(jb + 1, jb + 1 + N);
    long long ans = 0;
    priority_queue<int, vector<int>, greater<int>> q;
    for (i = 1; i <= N; ++i) {
        if (jb[i].prereq == 0) {
            q.push(jb[i].t);
        } else {
            pos = i;
            break;
        }
    }

    i = 0;
    while (!q.empty() && K > 0) {
        ans += q.top();
        K--;
        q.pop();
        i++;
        while (pos <= N && jb[pos].prereq <= i) {
            q.push(jb[pos++].t);
        }
    }

    if (K > 0) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    printf("%lld\n", ans);
    return 0;
}