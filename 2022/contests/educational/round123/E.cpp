// #define D
#define MAX_SIZE 1048597
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
struct segt {
    int lz, mn, len, cnt;
};

segt tree[MAX_SIZE];
vector<int> disc;

segt pullup(segt t1, segt t2) {
    segt ret = tree[0];
    ret.len = t1.len + t2.len;
    ret.lz = 0;
    ret.mn = min(t1.mn, t2.mn);
    ret.cnt = (t1.mn == ret.mn) * t1.cnt + (t2.mn == ret.mn) * t2.cnt;
    return ret;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].mn += tree[index].lz;
            tree[RIGHT].mn += tree[index].lz;
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
        }

        tree[index].lz = 0;
    }
}

void build(int l, int r, int index) {
    if (l > r) return;
    if (l == r) {
        tree[index].len = disc[l+1] - disc[l];
        tree[index].mn = 0;
        tree[index].cnt = disc[l+1] - disc[l];
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void update(int start, int end, int l, int r, int index, int v) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].lz += v;
        tree[index].mn += v;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, v);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, v);
    } else {
        update(start, end, l, MID, LEFT, v);
        update(start, end, MID + 1, r, RIGHT, v);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

int query() {
    return tree[1].len - tree[1].cnt * (tree[1].mn == 0);
}

vector<int> discy;
vector<int> tmpx, tmpy;
vector<pair<int, pair<int, int>>> add;
vector<pair<int, pair<int, int>>> del;
char s[MAX_SIZE];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i, j, k;
        int x = 1, y = 1;
        scanf("%d", &N);
        scanf("%s", s + 1);
        int M = strlen(s + 1);
        disc.clear();
        discy.clear();
        tmpx.clear();
        tmpy.clear();
        add.clear();
        del.clear();

        for (i = 1; i <= M; ++i) {
            if (s[i] == 'D') {
                y++;
            } else {
                x++;
            }
        }

        int tx = 1, ty = 1;
        bool meetD = false,  meetR = false;
        for (i = 1; i <= M; ++i) {
            int x1 = tx, x2 = tx, y1 = ty, y2 = ty;
            if (meetD) {
                y2 = y2 + (N - y);
            }

            if (meetR) {
                x2 = x2 + (N - x);
            }

            tmpx.push_back(x1);
            tmpx.push_back(x2 + 1);
            tmpy.push_back(y1);
            tmpy.push_back(y2 + 1);
            add.push_back(make_pair(y1, make_pair(x1, x2 + 1)));
            del.push_back(make_pair(y2 + 1, make_pair(x1, x2 + 1)));
            meetD |= (s[i] == 'D');
            meetR |= (s[i] == 'R');
            if (s[i] == 'D') {
                ty++;
            } else {
                tx++;
            }
        }

        int x1 = tx, x2 = tx, y1 = ty, y2 = ty;
        if (meetD) {
            y2 = y2 + (N - y);
        }

        if (meetR) {
            x2 = x2 + (N - x);
        }

        tmpx.push_back(x1);
        tmpx.push_back(x2 + 1);
        tmpy.push_back(y1);
        tmpy.push_back(y2 + 1);
        add.push_back(make_pair(y1, make_pair(x1, x2 + 1)));
        del.push_back(make_pair(y2 + 1, make_pair(x1, x2 + 1)));
        sort(tmpx.begin(), tmpx.end());
        sort(tmpy.begin(), tmpy.end());

        for (i = 0 ; i < (int) tmpx.size(); ++i) {
            if (i == 0 || tmpx[i] != tmpx[i-1]) {
                disc.push_back(tmpx[i]);
            }
        }

        for (i = 0 ; i < (int) tmpy.size(); ++i) {
            if (i == 0 || tmpy[i] != tmpy[i-1]) {
                discy.push_back(tmpy[i]);
            }
        }
        
        sort(add.begin(), add.end());
        sort(del.begin(), del.end());
        int sz = disc.size() - 1;
        ll ans = 0;
        build(0, sz - 1, 1);
        for (i = 0, j = 0, k = 0 ; i < (int) discy.size(); ++i) {
            if (i >= 1) {
                ans = ans + 1ll * query() * (discy[i] - discy[i-1]);
            }

            while (j < (int) add.size() && add[j].first == discy[i]) {
                int l = lower_bound(disc.begin(), disc.end(), add[j].second.first) - disc.begin();
                int r = lower_bound(disc.begin(), disc.end(), add[j].second.second) - disc.begin();
                update(l, r - 1, 0, sz - 1, 1, 1);
                debug("update [%d, %d] by 1\n", add[j].second.first, add[j].second.second);
                
                ++j;
            }

            while (k < (int) del.size() && del[k].first == discy[i]) {
                int l = lower_bound(disc.begin(), disc.end(), del[k].second.first) - disc.begin();
                int r = lower_bound(disc.begin(), disc.end(), del[k].second.second) - disc.begin();
                debug("update [%d, %d] by -1\n", del[k].second.first, del[k].second.second);
                update(l, r - 1, 0, sz - 1, 1, -1);
                ++k;
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}
