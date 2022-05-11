#include <bits/stdc++.h>
typedef long double ld;
const ld Pi = acos(-1.0);
using namespace std;
// C is the fixed point, AB has angle of 0 initially
/*
      A
b    /\ c
   C -- B 
     a 
*/

ld getlow(ld len, ld L, ld offset) {
    if (len <= L) return -offset;
    return acos(L/len) - offset;
}

ld gethigh(ld len, ld L, ld offset) {
    if (len <= L) return Pi / 2 - offset;
    return Pi / 2 - acos(L / len) - offset;
}

bool check(ld a, ld b, ld c, ld L) {
    ld theta = acos((a*a+b*b-c*c)/(a*b*2));
    if (theta > Pi / 2) return false;
    if (a > sqrt(2) * L) return false;
    if (b > sqrt(2) * L) return false;
    ld low = 0, high = (Pi / 2) - theta;
    low = max(low, getlow(b, L, theta));
    low = max(low, getlow(a, L, 0));
    high = min(high, gethigh(b, L, theta));
    high = min(high, gethigh(a, L, 0));
    //cout << (low * 180 / Pi) << " " << theta << endl;
    //cout << a << " " << b <<" " << c << endl;
    return low <= high;
}

int main() {
    ld a, b, c;
    cin >> a >> b >> c;
    int i;
    ld low = 0.2, high = 30000, ans = 30000;
    for (i = 0 ; i < 200; ++i) {
        ld mid = (low + high) / 2;
        if (check(a, b, c, mid) || check(a, c, b, mid) || check(b, c, a, mid) || check(b, a, c, mid) || check(c, a, b, mid) || check(c, b, a, mid)) {
            high = mid;
            ans = mid;
        } else {
            low = mid;
        }
    }

    printf("%.15Lf\n", ans);
    return 0;
}