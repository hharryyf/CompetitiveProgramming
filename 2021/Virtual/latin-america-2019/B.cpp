#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long double ld;
using namespace std;

const ld Pi = acos(-1.0);
pair<ld, ld> pt[MAX_SIZE];
int N;

void transform(ld &x, ld &y) {
    swap(x, y);
    x *= -1;
}

ld getlow(ld x, ld y, ld L) {
    return acos(L / sqrt(x*x+y*y));
}

ld getoff(ld x, ld y) {
    return atan2(y, x);
}

ld gethigh(ld x, ld y, ld L) {
    return Pi / 2 - acos(L / sqrt(x*x+y*y));
}

bool check(ld L) {
    ld low, high;
    vector<pair<ld, ld>> bad;
    int i;
    for (i = 0 ; i < N; ++i) {
        if (pt[i].first * pt[i].first + pt[i].second * pt[i].second > L * L * 2) continue;
        if (pt[i].first * pt[i].first + pt[i].second * pt[i].second <= L * L) return false;
        ld offset = getoff(pt[i].first, pt[i].second);
        low = getlow(pt[i].first, pt[i].second, L);
        high = gethigh(pt[i].first, pt[i].second, L);
        if (offset >= low && offset >= high) {
            ld tmpl = low, tmph = high;
            low = offset - tmph, high = offset - tmpl;
        } else if (low >= offset && high >= offset) {
            offset += Pi / 2;
            ld tmpl = low, tmph = high;
            low = offset - tmph, high = offset - tmpl;
        } else {
            ld tmpl = low, tmph = high;
            low = offset - tmph, high = offset - tmpl;
        }

        low -= Pi;
        high -= Pi;
        while (low <= Pi) {
            if (high >= 0) {
                bad.emplace_back(low, high);
            }
            low += Pi / 2;
            high += Pi / 2;
        }
    }
    //cout << "check " << L << endl;
    //cout << "bad interval " << bad.size() << endl;
    if ((int) bad.size() <= 1) return true;
    
    sort(bad.begin(), bad.end());
    ld mx = -100;
    for (i = 0 ; i < (int) bad.size(); ++i) {
        //cout << bad[i].first << ", " << bad[i].second << " ";
        if (i > 0 && bad[i].first - mx > 0) {
            //cout << endl;
            return true;
        }
        if (i == 0 && bad[i].first > 0) {
            return true;
        }
        mx = max(bad[i].second, mx);
    }

    return false;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%Lf%Lf", &pt[i].first, &pt[i].second);
        while (pt[i].first < 0 || pt[i].second < 0) transform(pt[i].first, pt[i].second);
        // cout  << pt[i].first << " " << pt[i].second << endl;
    }

    ld low = 0.1, high = 1e9, ans = 1e9;
    for (i = 0 ; i < 200; ++i) {
        ld mid = (low + high) / 2;
        if (check(mid)) {
            low = mid;
            ans = mid;
        } else {
            high = mid;
        }
    }

    cout << fixed << setprecision(4) << ans * 8 << endl;
    return 0;
}