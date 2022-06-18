#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005

int t;
string s;

bool possible(vector<int>& pos, int count, int n) {
  if (count == 0) return true;
  if (count > pos.size()) return false; // missed this case

  for (int s = 0; s < pos.size()-count+1; s++) {
    int e = s+count-1;
    // printf("%d %d %d\n", s, e, (int) pos.size());
    assert(e < pos.size());
    int others = (pos[e]-pos[s]+1)-count;
    if (s != 0) {
      others += pos[s]-pos[s-1]-1;
    } else {
      // missed this case
      others += pos[s];
    }
    if ((e+1) < pos.size()) {
      others += pos[e+1]-pos[e]-1;
    } else {
      others += n-(pos[e]+1);
    }
    if (others > count) {
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> t;
  while (t--) {
    vector<int> pos0;
    vector<int> pos1;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '0') {
        pos0.push_back(i);
      } else {
        pos1.push_back(i);
      }
    }

    int lo = 0;
    int hi = s.length() / 2;
    int best = -1;
    while (hi >= lo) {
      int mid = (lo+hi)/2;
      if (possible(pos0, mid, s.length()) || possible(pos1, mid, s.length())) {
        lo = mid+1;
        best = mid;
      } else {
        hi = mid-1;
      }
    }
    cout << best << endl;
  }
}
