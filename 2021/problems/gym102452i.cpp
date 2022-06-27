#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
typedef long long ll;
int N, M;
// watched[i] all the limits at for location i, denotes its next limit and member_id related to that location
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> watched[MAX_SIZE];
// if the ith member has been printed
int visited[MAX_SIZE];
ll need[MAX_SIZE];
// total time on the ith observing point
ll toltime[MAX_SIZE];
// initial time of the ith member
ll initime[MAX_SIZE];
// associated locations
vector<int> g[MAX_SIZE];
// add location x by y
int update(int x, int y) {
    toltime[x] += y;
    vector<int> ans;
    while (!watched[x].empty()) {
        auto p = watched[x].top();
        if (p.first > toltime[x]) break;
        watched[x].pop();
        if (visited[p.second]) continue;
        // the pth get increased
        ll currtime = 0;
        for (auto cid : g[p.second]) {
            currtime += toltime[cid];
        }

        if (currtime >= initime[p.second] + need[p.second]) {
            visited[p.second] = 1;
            ans.push_back(p.second);
        } else {
            ll diff = initime[p.second] + need[p.second] - currtime;
            ll step = diff / 3 + (diff % 3 != 0);
            for (auto cid : g[p.second]) {
                watched[cid].push({step + toltime[cid], p.second});
            }
        }
    }

    sort(ans.begin(), ans.end());
    int sz = ans.size();
    printf("%d", sz);
    for (auto v : ans) {
        printf(" %d", v);
    }
    printf("\n");
    return sz;
}

int main() {
    scanf("%d%d", &N, &M);
    int curr = 1, i;
    int last = 0;
    while (M-- > 0) {
        int tp;
        scanf("%d", &tp);
        if (tp == 1) {
            int k;
            scanf("%lld", &need[curr]);
            need[curr] ^= last;
            scanf("%d", &k);
            for (i = 0 ; i < k; ++i) {
                int v;
                scanf("%d", &v);
                v ^= last;
                g[curr].push_back(v);
                initime[curr] += toltime[v];
            }

            ll step = need[curr] / 3 + (need[curr] % 3 != 0);
            for (auto v : g[curr]) {
                // when the observing point v has increased by step, we should get notified
                watched[v].push({step + toltime[v], curr});
            }
            curr++;
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            x ^= last, y ^= last;
            last = update(x, y);
        }
    }
    return 0;
}