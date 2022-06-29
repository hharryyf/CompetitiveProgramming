#include <bits/stdc++.h>
#define MAX_SIZE 524292

typedef long long ll;

using namespace std;

ll arr[MAX_SIZE >> 1];

struct segt {
	ll maxl, maxr, value, rsum;
};

/* 
   1 a b query [a, b] maximum subarray sum
   2 a b   change arr[a] to b
*/

int N;
segt tree[MAX_SIZE];

segt pullup(segt t1, segt t2) {
	segt t;
	t.maxl = max(t1.maxl, t1.rsum + t2.maxl);
	t.maxr = max(t2.maxr, t2.rsum + t1.maxr);
	t.rsum = t1.rsum + t2.rsum;
	t.value = max(max(t1.value, t2.value), t1.maxr + t2.maxl);
	return t;
}

void build(int l, int r, int index) {
	if (l > r) return;
	if (l == r) {
		tree[index].maxl = tree[index].maxr = tree[index].value = arr[l];
		tree[index].rsum = arr[l];
		return;
	}
	
	int mid = l + (r - l) / 2;
	build(l, mid, index * 2);
	build(mid + 1, r, index * 2 + 1);
	tree[index] = pullup(tree[index * 2], tree[index * 2 + 1]);
}

segt query(int start, int end, int l, int r, int index) {
	if (start > end || l > r || start > r || l > end) return segt{0,0,0,0};
	if (start <= l && r <= end) return tree[index];
	int mid = l + (r - l) / 2;
	if (end <= mid) return query(start, end, l, mid, index * 2);
	if (start >= mid + 1) return query(start, end, mid + 1, r, index * 2 + 1);
	return pullup(query(start, end, l, mid, index * 2), query(start, end, mid + 1, r, index * 2 + 1));
}

int mxL[MAX_SIZE], mxR[MAX_SIZE];

void findL() {
    vector<ll> pos;
    for (int i = 1; i <= N; ++i) {
        while (!pos.empty() && arr[pos.back()] <= arr[i]) pos.pop_back();
        if (!pos.empty()) {
            mxL[i] = pos.back();
        } else {
            mxL[i] = 0;
        }
        pos.push_back(i);
    }
}

void findR() {
    vector<ll> pos;
    for (int i = N; i >= 1; --i) {
        while (!pos.empty() && arr[pos.back()] <= arr[i]) pos.pop_back();
        if (!pos.empty()) {
            mxR[i] = pos.back();
        } else {
            mxR[i] = N + 1;
        }
        pos.push_back(i);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) scanf("%lld", &arr[i]);
        build(1, N, 1);
        findL();
        findR();
        bool bad = false;
        for (i = 1; i <= N; ++i) {
            ll qL = query(mxL[i] + 1, i - 1, 1, N, 1).maxr;
            ll qR = query(i + 1, mxR[i] - 1, 1, N, 1).maxl;
            // printf("i = %d, ql = %lld qr = %lld l = %d r = %d\n", i, qL, qR, mxL[i], mxR[i]);
            if (qL > 0 || qR > 0) {
                bad = true;
                break;
            }
        }

        if (bad) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
    return 0;
}