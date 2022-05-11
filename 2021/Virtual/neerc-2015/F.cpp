#include <bits/stdc++.h>
#define MAX_SIZE 3111
#define SUBMIT
using namespace std;
typedef double ld;
typedef int ll;
struct point {
    ll x, y;
    bool operator < (point other) const {
        return x < other.x;
    }
};

vector<int> L, R;
ld ansx, ansy;
point pt[MAX_SIZE];
int f[MAX_SIZE];
int N;
ll w;

ld sqr(ld x) {
    return x * x;
}

ld dist(point p1, point p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int u, int v) {
    int a = find(u), b = find(v);
    f[a] = b;
}

bool check(ld d) {
    int i, j;
    for (i = 1; i <= N; ++i) {
        f[i] = i;
    }

    for (i = 0 ; i < (int) L.size() - 1; ++i) {
        unionset(L[i], L[i + 1]);
    }

    for (i = 0 ; i < (int) R.size() - 1; ++i) {
        unionset(R[i], R[i + 1]);
    }


    for (i = 1; i <= N; ++i) {
        for (j = i + 1; j <= N; ++j) {
            if (dist(pt[i], pt[j]) <= d * d && find(i) != find(j)) {
                unionset(i, j);
            }
        }
    }

    int f1 = find(L[0]), f2 = find(R[0]);
    if (f1 == f2) {
        ansx = 0.5, ansy = 0.5;
        return true;
    }

    for (i = 1; i <= N; ++i) {
        if (find(i) != f1) continue;
        for (j = 1; j <= N; ++j) {
            if (find(j) == f2) {
                if (dist(pt[i], pt[j]) <= d * d * 4.0) {
                    ansx = 1.0 * (pt[i].x + pt[j].x) / 2.0;
                    ansy = 1.0 * (pt[i].y + pt[j].y) / 2.0;
                    return true;
                }
            }
        }
    }
    return false;
};

int main() {
    int i;
    #ifdef SUBMIT
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    #endif
    scanf("%d%d", &w, &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%d", &pt[i].x, &pt[i].y);
    }
    if (N == 0) {
        ansx = 1.0 * w / 2, ansy = 0;
        printf("%.10lf %.10lf\n", ansx, ansy);
        return 0;
    }
    int tol = N;
    for (i = 1; i <= N; ++i) {
        pt[++tol] = pt[i];
        pt[tol].x = 0;
        pt[++tol] = pt[i];
        pt[tol].x = w;
    }
    N = tol;
    // cout << N << endl;
    for (i = 1; i <= N; ++i) {
        if (pt[i].x == 0) L.push_back(i);
        if (pt[i].x == w) R.push_back(i);
    }

    ld low = 0, high = w, ans = w;
    for (i = 1; i <= 40; ++i) {
        if (low > high) continue;
        ld mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid;
        } else {
            low = mid;
        }
    }

    check(ans);
    printf("%.10lf %.10lf\n", ansx, ansy);
    return 0;
}