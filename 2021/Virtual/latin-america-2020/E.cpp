#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100011
int N;
pair<int, int> q[MAX_SIZE];
int ans[MAX_SIZE];
set<int> pos;

void update(int l, int r) {
    if (l > r) return;
    ans[l] += 1, ans[r+1] -= 1;
    // cout << "update " << l << " " << r << endl;
}

int getlow(int p) {
    return *prev(pos.lower_bound(p));
}

int gethigh(int p) {
    return *pos.upper_bound(p);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &q[i].first);
        q[i].second = i;
    }

    pos.insert(0);
    pos.insert(N+1);

    sort(q + 1, q + 1 + N);
    for (i = N; i >= 1; --i) {
        // cout << "consider building " << q[i].second << endl;
        int L = getlow(q[i].second), R = gethigh(q[i].second), x = q[i].second;
        // first we solve the left interval
        // left interval means [L+1, x - 1]
        // [6 7 8 9]
        // [6 7 8 9 10] 
        if (L + 1 <= x - 1) {
            if (L == 0) {
                update(L + 1, x - 1);
            } else {
                update(1 + (L + x) / 2, x - 1);
            }
        }

        // next we solve the right interval
        // right interval means [x + 1, R - 1]
        if (x + 1 <= R - 1) {
            if (R == N + 1) {
                update(x + 1, R - 1);
            } else {
                update(x + 1, -1 + (R + x + 1) / 2);
            }
        }
        /*
        // consider the left peak
        if (L != 0) {
            int ll = getlow(L);
            if (ll == 0 || L - ll > x - L) update(L, L);
        }

        // consider the right peak
        if (R != N + 1) {
            int rr = gethigh(R);
            if (rr == N + 1 || rr - R > R - x) update(R, R);
        }*/

        pos.insert(q[i].second);
    }

    for (i = 1; i <= N; ++i) {
        ans[i] += ans[i-1];
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}