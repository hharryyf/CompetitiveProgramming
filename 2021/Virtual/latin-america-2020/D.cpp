#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int>> q;
int N;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        int v;
        scanf("%d", &v);
        q.push(v);
    }

    int meet = 0;
    if ((int) q.size() < 2) {
        printf("N\n");
        return 0;
    }

    if ((int) q.size() == 2) {
        printf("Y\n");
        return 0;
    }

    while ((!meet && (int) q.size() > 2) || (meet && q.size() > 1)) {
        if (!meet) {
            int v1 = q.top();
            q.pop();
            int v2 = q.top();
            q.pop();
            if (v1 == v2) {
                q.push(v1 + 1);
            } else {
                q.push(v2);
                meet = 1;
            }
        } else {
            int v1 = q.top();
            q.pop();
            int v2 = q.top();
            q.pop();
            if (v1 == v2) {
                q.push(v1 + 1);
            } else {
                printf("N\n");
                return 0;
            }
        }
    }

    printf("Y\n");
    return 0;
}