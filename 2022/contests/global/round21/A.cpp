#include <bits/stdc++.h>
using namespace std;

int t, n, z, a;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		cin >> n >> z;
		int answer = -1;
		for (int i = 1; i <= n; i++) {
			cin >> a;
			answer = max(answer, a | z);
		}
		cout << answer << endl;
	}
}