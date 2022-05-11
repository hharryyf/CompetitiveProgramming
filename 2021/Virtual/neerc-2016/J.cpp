/*
    Not my code, Dallas coded it on contest
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

#define MAXN 10001
#define MAXH 5001

ll n,w,h,m;
ll removed[MAXH][2];
ll counts[MAXH];
ll center[MAXH];
bool pos[MAXH][MAXN];
ll outs[MAXH][2];

int main() {
    FILE *inf = fopen("jenga.in","r");
    FILE *ouf = fopen("jenga.out","w");
    fscanf(inf,"%lld %lld",&n,&w);
    fscanf(inf,"%lld %lld",&h,&m);
    for (ll i=0;i<m;i++) {
        fscanf(inf,"%lld %lld",&removed[i][0],&removed[i][1]);
        removed[i][0]--;
        removed[i][1]--;
    }
    fclose(inf);
    for (ll i=0;i<h;i++) {
        outs[i][1] = 2*(n-1);
        counts[i] = n;
        for (ll j=0;j<n;j++) {
            center[i] += j*2;
        }
    }
    for (ll i=0;i<m;i++) {
        // cout << "HI" << endl;
        counts[removed[i][0]]--;
        if (counts[removed[i][0]] == 0) {
            // cout << "FAIL" << endl;
            fprintf(ouf,"yes\n%lld\n",i+1);
            fclose(ouf);
            return 0;
        }
        pos[removed[i][0]][removed[i][1]] = true;
        center[removed[i][0]] -= removed[i][1]*2;
        for (ll j=0;j<n;j++) {
            if (!pos[removed[i][0]][j]) {
                outs[removed[i][0]][0] = j*2;
                break;
            }
        }
        for (ll j=n-1;j>=0;j--) {
            if (!pos[removed[i][0]][j]) {
                outs[removed[i][0]][1] = j*2;
                break;
            }
        }
        // cout << "HI4" << endl;
        // center[removed[i][0]] /= counts[removed[i][0]];
        ld curC[2] = {0};
        ll prevSum = 0;
        // cout << "HI2" << endl;
        for (ll j=h-1;j>=0;j--) {
            // cout << curC[0] << " " << curC[1] << " " << prevSum << " " << outs[j][0] << " " << outs[j][1] << " " << center[j] << endl;
            // cout << prevSum << endl;
            if (j%2) {
                if (prevSum > 0 && (curC[1] <= (outs[j][0]-1)*prevSum || curC[1] >= (outs[j][1]+1)*prevSum)) {
                    fprintf(ouf,"yes\n%lld\n",i+1);
                    fclose(ouf);
                    return 0;
                }
                curC[0] += (n-1)*counts[j];
                curC[1] = (curC[1] + center[j]);
            } else {
                if (prevSum > 0 && (curC[0] <= (outs[j][0]-1)*prevSum || curC[0] >= (outs[j][1]+1)*prevSum)) {
                    fprintf(ouf,"yes\n%lld\n",i+1);
                    fclose(ouf);
                    return 0;
                }
                curC[0] = (curC[0] + center[j]);
                curC[1] += (n-1)*counts[j];
            }
            prevSum += counts[j];
        }
        // cout << endl;
    }
    fprintf(ouf,"no\n");
    fclose(ouf);
    return 0;
}