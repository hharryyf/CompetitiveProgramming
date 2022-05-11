#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

const ll inf = 2e9 + 7;

vector<int> g[MAX_SIZE];
set<pair<int, int>> pt;
pair<int, int> coord[MAX_SIZE];
vector<int> tmp, disc;
vector<int> light, heavy;
int N, x[MAX_SIZE];


bool haspoint(int x, int y) {
    return pt.find({x, y}) != pt.end();
}

void init() {
    pt.clear();
    tmp.clear();
    disc.clear();
    light.clear();
    heavy.clear();
}

int main() {
    int i, j;
    while (scanf("%d", &N) != EOF) {
        init();
        for (i = 0 ; i < N; ++i) {
            g[i].clear();
            scanf("%d%d", &coord[i].first, &coord[i].second);
            tmp.push_back(coord[i].first);
            pt.insert({coord[i].first, coord[i].second});
        }

        sort(tmp.begin(), tmp.end());
        for (i = 0 ; i < (int) tmp.size(); ++i) {
            if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
        }

        int sz = disc.size(), block_sz = sqrt(N);
        for (i = 0 ; i < sz; ++i) {
            x[i] = disc[i];
        }

        for (i = 0 ; i < N; ++i) {
            int idx = lower_bound(disc.begin(), disc.end(), coord[i].first) - disc.begin();
            g[idx].push_back(coord[i].second);
        }
        
        
        int ans = 0;
        for (i = 0 ; i < sz; ++i) {
            if ((int) g[i].size() <= block_sz) {
                light.push_back(i);
            } else {
                heavy.push_back(i);
            }
        }

        // process the light chain of points
        for (auto id : light) {
            for (i = 0 ; i < (int) g[id].size(); ++i) {
                for (j = i + 1; j < (int) g[id].size(); ++j) {
                    int d = g[id][i] - g[id][j];
                    if (d < 0) d = -d;
                    if (haspoint(x[id] + d, g[id][i]) && haspoint(x[id] + d, g[id][j])) ans = max(ans, d);
                    else if (haspoint(x[id] - d, g[id][i]) && haspoint(x[id] - d, g[id][j])) ans = max(ans, d);
                }
            }
        }       

        for (i = 0 ; i < (int) heavy.size(); ++i) {
            for (j = i + 1 ; j < (int) heavy.size(); ++j) {
                for (auto y : g[heavy[i]]) {
                    int d = x[heavy[j]] - x[heavy[i]];
                    if (d < 0) d = -d;
                    if (haspoint(x[heavy[j]], y) && haspoint(x[heavy[i]], y + d) && haspoint(x[heavy[j]], y + d)) ans = max(ans, d);
                    else if (haspoint(x[heavy[j]], y) && haspoint(x[heavy[i]], y - d) && haspoint(x[heavy[j]], y - d)) ans = max(ans, d);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}