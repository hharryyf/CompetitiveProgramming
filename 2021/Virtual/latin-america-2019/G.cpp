#include <bits/stdc++.h>
#define MAX_SIZE 524292
#define MAXLOG 20
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;
struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = (MAX_SIZE >> 1);
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
        memset(rank, 0, sizeof(rank));
    }

    void sort_cyclic_shifts(vector<int> &s) {
        int h, i;
        n = (int) s.size();    
        for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2]+1;
        for (i = 0; i < n; i++)
            cnt[s[i]]++;
        for (i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[0][p[0]] = 0;
        int classes = 1;
        for (i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        for (h = 0; (1 << h) < n; ++h) {
            for (i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt, cnt + classes, 0);
            for (i = 0; i < n; i++)
                cnt[c[h][pn[i]]]++;
            for (i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (i = n-1; i >= 0; i--)
                p[--cnt[c[h][pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (i = 1; i < n; i++) {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            
            for (i = 0 ; i < n; ++i) {
                c[h+1][i] = cn[i];
            }
        }

        for (i = 0 ; i < n; ++i) rank[p[i]] = i;
    }

    int lcp(int i, int j) {
        int ans = 0, k;
        for (k = logs[n]; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
};

SA sa;
int table[20][MAX_SIZE];
int logs[MAX_SIZE];

void precompute() {
    int i;
    for (i = 2; i < MAX_SIZE; i++) {
        logs[i] = logs[i/2] + 1;
    }
}

int RMQ(int l, int r) {
    if (l > r) return 4 * MAX_SIZE;
    int len = r - l + 1;
    return min(table[logs[len]][l], table[logs[len]][r - (1 << logs[len]) + 1]);
}

void build() {
    int i, j;
    for (i = 0; i < sa.n; i++) {
        table[0][i] = sa.p[i];
    }
    
    for (i = 1; i <= 19; i++) {
        int prel = (1 << (i - 1));
        for (j = 0; j < sa.n; j++) {
            if (j + prel < sa.n) {
                table[i][j] = min(table[i-1][j], table[i-1][j+prel]);
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
}

int N, Q;
char s[MAX_SIZE];
vector<int> curr;
vector<int> idx[MAX_SIZE];

int getLeft(int id) {
    int low = 0, high = id - 1, ret = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (RMQ(mid, id - 1) < N) {
            ret = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ret;
}

int getRight(int id) {
    int low = id + 1, high = sa.n - 1, ret = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (RMQ(id + 1, mid) < N) {
            ret = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ret;
}

int main() {
    int i, cnt = 28, id = 0;
    precompute();
    scanf("%s", s);
    N = strlen(s);
    for (i = 0; i < N; ++i) {
        curr.push_back(s[i] - 'A' + 1);
        id++;
    }
    curr.push_back(cnt++);
    id++;
    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        scanf("%s", s);
        int len = strlen(s);
        for (int j = 0 ; j < len; ++j) {
            curr.push_back(s[j] - 'A' + 1);
            idx[i].push_back(id++);
        }
        curr.push_back(cnt++);
        id++;
    }

    sa.sort_cyclic_shifts(curr);/*
    for (auto v : curr) {
        printf("%d ", v);
    }
    printf("\n");*/
    build();
    /*
    for (i = 0 ; i < sa.n; ++i) {
        printf("%d ", table[0][i]);
    }
    printf("\n");*/
    for (i = 1; i <= Q; ++i) {
        bool valid = true;
        int j = 0, cnt = 0;
        while (j < (int) idx[i].size()) {
            int L = getLeft(sa.rank[idx[i][j]]), R = getRight(sa.rank[idx[i][j]]);
            int len = -1;
            if (L != -1) {
                len = max(len, sa.lcp(sa.p[L], idx[i][j]));
                //printf("L= %d, len=%d\n", L, len);
            }

            if (R != -1) {
                len = max(len, sa.lcp(sa.p[R], idx[i][j]));
                //printf("R= %d, len=%d\n", R, len);
            }

            if (len <= 0) {
                valid = false;
                break;
            }
            j = j + len;
            cnt++;
        }

        if (!valid) {
            printf("-1\n");
        } else {
            printf("%d\n", cnt);
        }
    }
    return 0;
}