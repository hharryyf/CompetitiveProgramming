#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
typedef long long ll;
#define MAX_SIZE 200011
using namespace std;

struct events {
    ll x;
    int tp;
    ll p;
    bool operator < (events &other) const {
        if (x != other.x) return x < other.x;
        return tp > other.tp;
    }
};

vector<events> evt;
vector<ll> xcoord;
vector<ll> people;
vector<ll> tmp, disc;
int N, M;

int main() {
    int i, j;
    scanf("%d%d", &N, &M);
    people = vector<ll>(N, 0);
    xcoord = vector<ll>(M, 0);
    // number of person in each hub, coordinate = i * 400
    for (i = 0 ; i < N; ++i) scanf("%lld", &people[i]);
    // the position of each shop
    for (i = 0 ; i < M; ++i) {
        scanf("%lld", &xcoord[i]);
        xcoord[i] = xcoord[i] * 4;
    }

    sort(xcoord.begin(), xcoord.end());

    // for each hub, we find the interval of ice-cream shop
    // such that the people in the hub can go to the new ice-cream shop 
    for (i = 0; i < N; ++i) {
        ll pos = i * 400;
        if (pos > xcoord.back()) {
            evt.push_back(events{xcoord.back() + 1, 1, people[i]}); 
            evt.push_back(events{pos * 2 - xcoord.back(), 0, people[i]}); 
            tmp.push_back(xcoord.back() + 1);
            tmp.push_back(pos * 2 - xcoord.back());
        } else if (pos < xcoord[0]) {
            evt.push_back(events{pos * 2 - xcoord[0] + 1, 1, people[i]});
            evt.push_back(events{xcoord[0], 0, people[i]});
            tmp.push_back(pos * 2 - xcoord[0] + 1);
            tmp.push_back(xcoord[0]);
        } else {
            int id = lower_bound(xcoord.begin(), xcoord.end(), pos) - xcoord.begin();
            if (xcoord[id] == pos) continue;
            // id - 1 and id
            evt.push_back(events{max(xcoord[id-1] + 1, pos * 2 - xcoord[id] + 1), 1, people[i]});
            evt.push_back(events{min(xcoord[id], pos * 2 - xcoord[id-1]), 0, people[i]});
            tmp.push_back(max(xcoord[id-1] + 1, pos * 2 - xcoord[id] + 1));
            tmp.push_back(min(xcoord[id], pos * 2 - xcoord[id-1]));
        }
    }

    sort(tmp.begin(), tmp.end());
    sort(evt.begin(), evt.end());
    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
    }

    ll ans = 0, curr = 0;
    for (i = 0, j = 0; i < (int) disc.size(); ++i) {
        while (j < (int) evt.size() && evt[j].x == disc[i]) {
            if (evt[j].tp == 1) {
                curr = curr + evt[j].p;
            } else {
                curr = curr - evt[j].p;
            }
            ++j;
        }

        ans = max(ans, curr);
    }
    printf("%lld\n", ans);
    return 0;
}