#include <bits/stdc++.h>
using namespace std;
#define MAXN 50005
#define lli long long int

lli t, n, m, k;
lli a[MAXN];
lli b[MAXN];

// item remaining after dividing by m as many times as possible
lli item(lli x) {
	while (x % m == 0) {
		x /= m;
	}
	return x;
}

lli attainable(lli bval, lli val) {
	while (val < bval) val *= m;
	return val == bval;
}

bool solve() {
	// greedily break up a using m
	// consume as many items of a as possible
	lli val = item(a[1]);
	lli mul = 0;
	lli apos = 1;
	while (apos <= n && item(a[apos]) == val) {
		mul += a[apos] / item(a[apos]);
		apos += 1;
	}

	bool unsolvable = false;
	for (int bpos = 1; bpos <= k; bpos++) {
		// consume what is currently at val
		// or combinations of it
		if (b[bpos] == val) {
			if (mul == 0) {
				return false;
			}
			mul -= 1;
		} else if (attainable(b[bpos], val)) {
            if ((b[bpos] / val) > mul) {
            	return false;
            }
            mul -= (b[bpos] / val);
		} else {
			return false;
		}

		if (mul == 0) {
			// replenish using the next item
			if (apos <= n) {
				val = item(a[apos]);
				mul = 0;
				while (apos <= n && item(a[apos]) == val) {
					mul += a[apos] / item(a[apos]);
					apos += 1;
				}
			}
		}
	}
	if (mul) {
		return false; // still items remaining in A
	}
	return true; // all items of b have been satisfied
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		cin >> k;
		for (int i = 1; i <= k; i++) cin >> b[i];
		if (solve()) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
}