/*
    Not my code, Dallas coded it in contest
*/
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

#define MAXT 50001
const ll MAXK = 1e18+1;

ll t;
ll num;

ll npk[21][21];
ll nck[21][21];

ll pow(ll x, ll k) {
    if (k == 0) {return 1;}
    ll a = pow(x,k/2);
    a = a*a;
    if (k%2 == 1) {a = a*x;}
    return a;
}

void calc() {
    npk[0][0] = 1;
    for (ll i=1;i<21;i++) {
        npk[i][i] = (i*npk[i-1][i-1]);
    }
}

ll comb(ll n,ll k) {
    // cout << n << " " << k << endl;
    return (npk[n][n]/npk[k][k])/(npk[n-k][n-k]);
}

void solve() {
    ll out = 1;
    vector<ll> fingerprint;
    ll cur = 2;
    while (num != 0) {
        fingerprint.push_back(num%cur);
        num /= cur;
        cur++;
    }
    sort(fingerprint.begin(),fingerprint.end());
    reverse(fingerprint.begin(),fingerprint.end());
    fingerprint.push_back(-1);
    ll used = 0;
    ll prev = -1;
    ll count = 0;
    for (ll x : fingerprint) {
        if (x == prev) {
            count++;
        } else {
            if (prev != -1) {
                out *= comb(fingerprint.size()-1-max(prev-1,(ll)0)-used,count);
                used += count;
            }
            prev = x;
            count = 1;
        }
        // cout << x << " " << count << " " << out << endl;
    }
    // cout << out << endl;
    used = 0;
    prev = -1;
    count = 0;
    if (fingerprint[fingerprint.size()-2] == 0) {
        ll out2 = 1;
        fingerprint.pop_back();
        fingerprint.pop_back();
        fingerprint.push_back(-1);
        for (ll x : fingerprint) {
            if (x == prev) {
                count++;
            } else {
                if (prev != -1) {
                    if (fingerprint.size()-1-max(prev-1,(ll)0)-used < count) {
                        out2 = 0;
                        break;
                    }
                    out2 *= comb(fingerprint.size()-1-max(prev-1,(ll)0)-used,count);
                    used += count;
                }
                prev = x;
                count = 1;
            }
        }
        out -= out2;
    }
    printf("%lld\n",out-1);
}

int main() {
    scanf("%lld",&t);
    calc();
    for (ll casen=0;casen<t;casen++) {
        scanf("%lld",&num);
        solve();
    }
}