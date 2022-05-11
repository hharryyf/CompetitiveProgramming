#include <bits/stdc++.h>
using namespace std;

int earlyday[2111], lateday[2111];

void solve(int yy, int mm, int dd, int h, int m, int s) {
    int early = earlyday[yy], late = lateday[yy];
    if (mm == 3 && dd == early) {
        if (h == 2) {
            printf("Neither\n");
        } else if (h >= 3) {
            printf("PDT\n");
        } else {
            printf("PST\n");
        }
    } else if (mm == 11 && dd == late) {
        if (h == 1) {
            printf("Both\n");
        } else if (h == 0) {
            printf("PDT\n");
        } else {
            printf("PST\n");
        }
    } else {
        if ((mm == 11 && dd > late) || mm == 12 || mm == 1 || mm == 2 || (mm == 3 && dd < early)) {
            printf("PST\n");
        } else {
            printf("PDT\n");
        }
    }
}

bool isleap(int yy) {
    if (yy % 400 == 0) return true;
    if (yy % 100 == 0) return false;
    return yy % 4 == 0;
}

int numday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct datetime {
    int yy, mm, dd, wd;
    datetime nextd() {
        if (isleap(yy) && mm == 2 && dd == 28) {
            return {yy, mm, dd + 1, (wd + 1) % 7};
        } 

        if (dd >= numday[mm]) {
            if (mm == 12) {
                return {yy + 1, 1, 1, (wd + 1) % 7};
            }

            return {yy, mm + 1, 1, (wd + 1) % 7};
        }

        return {yy, mm, dd + 1, (wd + 1) % 7};
    }
};

void init() {
    datetime d = {2007, 3, 4, 0};
    while (true) {
        //cout << d.yy << " " << d.mm << " " << d.dd << " " << d.wd << endl;
        if (d.yy > 2100) break;
        if (d.mm == 3 && earlyday[d.yy] == 0 && d.wd == 0) {
            earlyday[d.yy] = -1;
        } else if (d.mm == 3 && earlyday[d.yy] == -1 && d.wd == 0) {
            earlyday[d.yy] = d.dd;
            //printf("early yy=%d, dd=%d\n", d.yy, d.dd);
        }  

        if (d.mm == 11 && !lateday[d.yy] && d.wd == 0) {
            lateday[d.yy] = d.dd;
            //printf("late yy=%d, dd=%d\n", d.yy, d.dd);
        }

        d = d.nextd();
    }
}

int main() {
    int t, T;
    scanf("%d", &T);
    init();
    for (t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int yy, mm, dd, h, m, s;
        scanf("%d-%d-%d %d:%d:%d", &yy, &mm, &dd, &h, &m, &s);
        solve(yy, mm, dd, h, m, s);
    }
    return 0;
}