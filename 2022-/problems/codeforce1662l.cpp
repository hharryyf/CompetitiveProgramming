#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;
#define MAX_SIZE 1048597
#define MID ((l+r)>>1)
#define LEFT (index<<1)
#define RIGHT (index<<1|1)

int N;
ll V;
ll t[MAX_SIZE], a[MAX_SIZE];
ll tree[MAX_SIZE];
vector<ll> disc, tmp;
vector<pair<ll, ll>> d;

void update(int pt, int l, int r, int index, ll val) {
    if (l > r || pt < l || pt > r) return;
    if (l == r) {
        tree[index] = max(tree[index], val);
        return;
    }
    if (pt <= MID) {
        update(pt, l, MID, LEFT, val);
    } else {
        update(pt, MID + 1, r, RIGHT, val);
    }
    tree[index] = max(tree[LEFT], tree[RIGHT]);
}

ll query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return -10000000ll;
    if (start <= l && r <= end) return tree[index];
    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return max(query(start, end, l, MID, LEFT),  query(start, end, MID + 1, r, RIGHT));
}

int main() {
    int i;
    scanf("%d%lld", &N, &V);
    for (i = 1; i <= N; ++i) {
        scanf("%lld", &t[i]);
    }

    for (i = 1; i < MAX_SIZE; ++i) tree[i] =  -10000000ll;

    for (i = 1; i <= N; ++i) {
        scanf("%lld", &a[i]);
    }

    for (i = 1; i <= N; ++i) {
        d.emplace_back(V * t[i] - a[i], V * t[i] + a[i]);
        tmp.push_back(V * t[i] + a[i]);
    }
    d.emplace_back(0, 0);
    tmp.push_back(0);

    sort(d.begin(), d.end());
    sort(tmp.begin(), tmp.end());

    

    for (i = 0; i < N; ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    int sz = disc.size();
    ll ans = 0;
    bool flag = false;
    for (auto p : d) {
        
        if (flag) {
            ll x = p.second;
            int idx = lower_bound(disc.begin(), disc.end(), x) - disc.begin();
            ll v = query(0, idx, 0, sz - 1, 1);
            ans = max(ans, v + 1);
            update(idx, 0, sz - 1, 1, v + 1);
        }

        if (p.first == 0 && p.second == 0) {
            ll x = p.second;
            int idx = lower_bound(disc.begin(), disc.end(), x) - disc.begin();
            update(idx, 0, sz - 1, 1, 0ll);
            flag = true;
        }
    }

    printf("%lld\n", max(ans, 0ll));
    return 0;
}