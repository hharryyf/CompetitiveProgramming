#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;
typedef long double ld;
vector<pair<int, int>> g[MAX_SIZE];
int N;
vector<pair<ld, pair<int, int>>> itv;

struct Vector {
    int x, y;
};

int Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}



int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        int x, y, b;
        scanf("%d%d%d", &x, &y, &b);
        g[b].emplace_back(x, y);
    }

    for (i = 1000; i >= 1; --i) {
        if (g[i].empty()) continue;
        for (int j = i - 1; j >= 1; --j) {
            for (auto p : g[i]) {
                for (auto np : g[j]) {
                    itv.push_back(make_pair(atan2(np.second - p.second, np.first - p.first), make_pair(np.first - p.first, np.second - p.second)));
                }
            }
        }
    }

    if ((int) itv.size() < 2) {
        printf("Y\n");
        return 0;
    }

    sort(itv.begin(), itv.end());
    int sz = itv.size();
    for (i = 0 ; i < sz; ++i) {
        Vector v1 = {itv[i].second.first, itv[i].second.second};
        Vector v2 = {itv[(i + 1) % sz].second.first, itv[(i + 1) % sz].second.second};
        if (Cross(v1, v2) <= 0 && fabs(itv[i].first - itv[(i+1) % sz].first) >= 1e-9) {
            //cout << v1.x << " " << v1.y << ", " << v2.x << " " << v2.y << endl;
            printf("Y\n");
            return 0;
        }
    }
    printf("N\n");
    return 0;
}