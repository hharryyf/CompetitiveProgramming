#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

struct event {
    ll l, ti;
    int tp;
    bool operator < (event other) const {
        if (l != other.l) return l < other.l;
        if (tp != other.tp) return tp < other.tp;
        return ti < other.ti;
    }
};

vector<event> evt;
multiset<ll> st;
int N;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        ll l, r, t;
        scanf("%lld%lld%lld", &l, &r, &t);
        evt.push_back(event{l + t, t, 0});
        evt.push_back(event{r, t, 1});
    }

    sort(evt.begin(), evt.end());
    ll ans = 0, curr = 0;
    for (i = 0 ; i < (int) evt.size(); ++i) {
        if (!st.empty()) {
            ll cnt = (evt[i].l - curr) / (*st.begin());
            ans = ans + cnt;
            curr = curr + cnt * (*st.begin());
        }

        if (evt[i].tp) {
            st.erase(st.find(evt[i].ti));
        } else {
            if (curr <= evt[i].l - evt[i].ti) {
                curr = evt[i].l;
                ans++;
            }
            st.insert(evt[i].ti);
        }
    }

    printf("%lld\n", ans);
    return 0;
}