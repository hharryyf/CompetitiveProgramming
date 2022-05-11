#include <bits/stdc++.h>
const double Pi = acos(-1.0);
#define MAX_SIZE 200011
#define double long double
typedef long long ll;
using namespace std;
const double eps = 1e-10;
int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point {
    ll x, y;
    int id;
    point(ll x=0, ll y=0, int id=0) : x(x), y(y), id(id) {}
    point operator -(point other) {
        return point(x - other.x, y - other.y);
    }
    
    point operator +(point other) {
        return point(x + other.x, y + other.y);
    }
    
    bool operator < (point other) {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

bool cmp(point a, point b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(point a, point b, point c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<point>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    point p1 = a[0], p2 = a.back();
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == (int) a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == (int) a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

int N, ans[MAX_SIZE];

int main() {
    int i;
    scanf("%d", &N);
    vector<point> pt;
    for (i = 1; i <= N; ++i) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        pt.push_back(point(x, y, i));
    }

    convex_hull(pt);
    for (auto p : pt) {
        ans[p.id] = 1;
    }

    for (i = 1; i <= N; ++i) {
        if (ans[i]) {
            printf("N");
        } else {
            printf("Y");
        }
    }
    printf("\n");
    return 0;
}