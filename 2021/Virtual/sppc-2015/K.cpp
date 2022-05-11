#include <bits/stdc++.h>
#define MAX_SIZE 524312
typedef long long ll;
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;


vector<pair<int, int>> in[MAX_SIZE], out[MAX_SIZE];
struct segt {
    int value, lz, cnt;
};

segt tree[MAX_SIZE];
int N;

segt pullup(segt t1, segt t2) {
    segt ret;
    ret.lz = 0;
    ret.value = min(t1.value, t2.value);
    ret.cnt = t1.cnt * (t1.value == ret.value) + t2.cnt * (t2.value == ret.value);
    return ret;
}

void pushdown(int l, int r, int index) {
    if (l > r) return;
    if (tree[index].lz != 0) {
        if (l != r) {
            tree[LEFT].lz += tree[index].lz;
            tree[RIGHT].lz += tree[index].lz;
            tree[LEFT].value += tree[index].lz;
            tree[RIGHT].value += tree[index].lz;
        }
        tree[index].lz = 0;
    }
}

void update(int start, int end, int l, int r, int index, int val) {
    if (start > end || l > r || start > r || l > end) return;
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        tree[index].value += val;
        tree[index].lz += val;
        return;
    }

    if (end <= MID) {
        update(start, end, l, MID, LEFT, val);
    } else if (start >= MID + 1) {
        update(start, end, MID + 1, r, RIGHT, val);
    } else {
        update(start, end, l, MID, LEFT, val);
        update(start, end, MID + 1, r, RIGHT, val);
    }

    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

void build(int l, int r, int index) {
    if (l > r) return;
    tree[index].lz = 0;
    if (l == r) {
        tree[index].value = 0;
        tree[index].cnt = 1;
        return;
    }

    build(l, MID, LEFT);
    build(MID + 1, r, RIGHT);
    tree[index] = pullup(tree[LEFT], tree[RIGHT]);
}

segt query(int start, int end, int l, int r, int index) {
    if (start > end || l > r || start > r || l > end) return tree[0];
    pushdown(l, r, index);
    if (start <= l && r <= end) {
        return tree[index];
    }

    if (end <= MID) return query(start, end, l, MID, LEFT);
    if (start >= MID + 1) return query(start, end, MID + 1, r, RIGHT);
    return pullup(query(start, end, l, MID, LEFT), query(start, end, MID + 1, r, RIGHT));
}

void init() {
    int i;
    build(0, N - 1, 1);
    for (i = 0 ; i < N; ++i) {
        in[i].clear();
        out[i].clear();
    }
}

int decode(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
    return ch - 'a' + 36;
}

char s[8];

int main() {
    int i;
    while (scanf("%d", &N) != EOF) {
        init();
        bool valid = false;
        // the two line we add are ((i, bi), ai) and ((i, bi), i)
        for (i = 0 ; i < N; ++i) {
            scanf("%s", s);
            int ai = 62 * 62 * decode(s[0]) + 62 * decode(s[1]) + decode(s[2]), bi = 62 * 62 * decode(s[3]) + 62 * decode(s[4]) + decode(s[5]);
            ai = max(ai, 0), bi = min(bi, N - 1);
            if (ai == 0 && bi == N - 1) {
                valid = true;
            }
            
            in[ai].emplace_back(i, bi);
            out[i].emplace_back(i, bi);
        }

        for (i = 0 ; i < N; ++i) {
            in[i].emplace_back(i, i);
            out[i].emplace_back(i, i);
        }

        if (!valid) {
            printf("Bad\n");
            continue;
        }

        for (i = 0 ; i < N; ++i) {
            for (auto p : in[i]) {
                update(p.first, p.second, 0, N - 1, 1, 1);
                //cout << "Add " << p.first << " " << p.second << endl;
            }

            int cover = query(i, N-1,  0, N - 1, 1).value;
            //cout << "query " << i << " " << (N-1) << " query= " << cover << endl;
            if (cover == 0) {
                valid = false;
                break;
            } 

            for (auto p : out[i]) {
                update(p.first, p.second, 0, N - 1, 1, -1);
                //cout << "delete " << p.first << " " << p.second << endl;
            }
        }

        if (valid) {
            printf("Great\n");
        } else {
            printf("Acceptable\n");
        }
    }
    return 0;
}