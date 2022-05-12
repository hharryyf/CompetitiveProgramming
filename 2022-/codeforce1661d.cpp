#include <bits/stdc++.h>
//#define L
#ifdef L
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 1048597
typedef long long ll;

using namespace std;

struct segt {
    ll lz, value;
};

segt tree[MAX_SIZE];
int n, k;

void pushdown(int l, int r, int index) {
    if (l >= r) return;
    if (tree[index].lz || tree[index].value) {
        int mid = l + (r - l) / 2;
        int len = mid - l + 1;
        tree[index * 2].lz += tree[index].lz;
        tree[index * 2 + 1].lz += tree[index].lz;
        tree[index * 2].value += tree[index].value;
        tree[index * 2 + 1].value += tree[index].value + tree[index].lz  * len;
        tree[index].lz = 0;
        tree[index].value = 0;
    }
}

void update(int start, int end, int l, int r, int index, ll val) {
    if (start > end || l > r) return;
    int mid = l + (r - l) / 2;
    pushdown(l, r, index);
    if (start > r || l > end) return;
    if (start <= l && r <= end) {
        tree[index].value += val * (l - start + 1); 
        tree[index].lz += val;
        return;
    }
    
    if (end <= mid) {
        update(start, end, l, mid, index * 2, val);
    } else if (start >= mid + 1) {
        update(start, end, mid + 1, r, index * 2 + 1, val);
    } else {
        update(start, end, l, mid, index * 2, val);
        update(start, end, mid + 1, r, index * 2 + 1, val);
    }
}

ll query(int pos, int l, int r, int index) {
    if (l > r || pos < l || pos > r) return 0;
    pushdown(l, r, index);
    int mid = l + (r - l) / 2;
    if (l == r && r == pos) return tree[index].value;
    if (pos <= mid) return query(pos, l, mid, index * 2);
    return query(pos, mid + 1, r, index * 2 + 1);
}

ll b[MAX_SIZE];

int main() {
    int i;
    ll ans = 0;
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i) scanf("%lld", &b[i]);
    for (i = n; i >= k; --i) {
        ll curr = query(i, 1, n, 1);
        if (curr < b[i]) {
            ll need = (b[i] - curr) / k + ((b[i] - curr) % k != 0);
            ans = ans + need;
            // increase [i - k + 1, i] by an arithmetic progression of d = need
            update(i - k + 1, i, 1, n, 1, need);
        }
    }

    ll curr = 0;
    for (i = 1; i < k; ++i) {
        ll val = query(i, 1, n, 1);
        if (val < b[i]) curr = max(curr, (b[i] - val) / i + ((b[i] - val) % i != 0));
    }

    printf("%lld\n", ans + curr);
    return 0;
}