#include <bits/stdc++.h>
#define MAX_SIZE 100011
#define SUBMIT
typedef long long ll;
using namespace std;

ll ans[MAX_SIZE];

struct lines {
    ll y, len;
    bool operator < (lines other) const {
        return y < other.y;
    }
};

int N, Q;
vector<pair<ll, int>> q;
vector<lines> evt;
vector<ll> tmp;
vector<ll> disc;
ll curr = 0, currlen = 0, currans = 0, currt = 0;
char st[3];

int main() {
    #ifdef SUBMIT
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    #endif
    int i;
    scanf("%d%d", &N, &Q);
    for (i = 1; i <= N; ++i) {
        ll t;
        int k;
        scanf("%s%lld%d", st, &t, &k);
        if (st[0] == '+') {
            evt.push_back(lines{curr, t - currt});
            curr += k;
        } else {
            evt.push_back(lines{curr, t - currt});
            curr -= k;
        }
        currt = t;
    }

    for (i = 1; i <= Q; ++i) {
        ll t;
        scanf("%lld", &t);
        if (t + curr >= 0) {
            q.emplace_back(-t, i);
        } else {
            ans[i] = -1;
        }
    }

    sort(evt.begin(), evt.end());
    sort(q.begin(), q.end());
    for (auto v : evt) {
        tmp.push_back(v.y);
    }

    for (auto v : q) {
        tmp.push_back(v.first);
    }

    sort(tmp.begin(), tmp.end());

    for (i = 0; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }

    int j = 0, k = 0;
    for (i = 0 ; i < (int) disc.size(); ++i) {
        if (i != 0) {
            currans += 1ll * (disc[i] - disc[i-1]) * currlen;
        }

        while (j < (int) q.size() && q[j].first <= disc[i]) {
            ans[q[j++].second] = currans;
        }

        while (k < (int) evt.size() && evt[k].y <= disc[i]) {
            currlen += evt[k++].len;
        }
    }

    for (i = 1; i <= Q; ++i) {
        if (ans[i] == -1) {
            printf("INFINITY\n");
        } else {
            printf("%lld\n", ans[i]);
        }
    }
    return 0;
}