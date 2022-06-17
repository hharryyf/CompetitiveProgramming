#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define MAX_SIZE 52
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

const ll mod = 1e18 + 7;

inline ll add(ll x,ll y){
    return ((x + y) % mod + mod) % mod;
}

inline ll mul(ll x,ll y){
    return x * y % mod;
}

inline ll qpow(ll x,ll n){
    ll ret= 1;
    while(n > 0){
        if(n & 1) ret = mul(ret, x);
        x = mul(x, x);
        n >>= 1;
    }

    return ret;
}

ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

int query(int x1, int y1, int x2, int y2) {
    cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    cin >> x1;
    // we generate RE instead of WA if the query is invalid
    if (x1 == -1) exit(9);
    return x1;
}

int N;
int a[MAX_SIZE][MAX_SIZE];
vector<array<int, 3>> g[MAX_SIZE][MAX_SIZE];
int ivt = 0;

vector<pair<int, int>> good;
vector<pair<int, int>> curr;


void dfs(int x, int y) {
    for (auto v : g[x][y]) {
        int nx = v[0], ny = v[1], c = v[2];
        if (a[nx][ny] == -1) {
            a[nx][ny] = a[x][y] ^ c ^ 1;
            dfs(nx, ny);
        }
    }
}

bool valid(int x, int y) {
    return x > 0 && x <= N && y > 0 && y <= N;
}

void dfs2(int x, int y, int d) {
    if (d == 3) {
        int res = 0;
        for (auto p : curr) {
            res ^= a[p.first][p.second];
        }

        if (res == 0) {
            good = curr;
        }
        return;
    }

    if (valid(x + 1, y)) {
        curr.emplace_back(x + 1, y);
        dfs2(x + 1, y, d + 1);
        curr.pop_back();
    }

    if (valid(x, y + 1)) {
        curr.emplace_back(x, y + 1);
        dfs2(x, y + 1, d + 1);
        curr.pop_back();
    }
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            a[i][j] = -1;
        }
    }

    a[1][1] = 1, a[N][N] = 0;

    // solve all odd positions
    if (query(1, 1, 2, 2)) {
        a[2][2] = 1;
    } else {
        a[2][2] = 0;
    }

    for (i = 3; i <= N; i += 2) {
        a[1][i] = query(1, i - 2, 1, i) ^ a[1][i-2] ^ 1;
    }

    for (i = 4; i <= N - 1; i += 2) {
        a[2][i] = query(2, i - 2, 2, i) ^ a[2][i-2] ^ 1;
    }

    for (j = 1; j <= N; ++j) {
        if (j % 2 == 1) {
            for (i = 3; i <= N; i += 2) {
                if (a[i][j] == -1) {
                    int res = query(i - 2, j, i, j);
                    if (a[i-2][j] == 1) {
                        a[i][j] = res;
                    } else {
                        a[i][j] = res ^ 1;
                    }
                }
            }
        } else {
            for (i = 2; i <= N - 1; i += 2) {
                if (a[i][j] == -1) {
                    int res = query(i - 2, j, i, j);
                    if (a[i-2][j] == 1) {
                        a[i][j] = res;
                    } else {
                        a[i][j] = res ^ 1;
                    }
                }
            }
        }
    }
    
    // deal with the even positions
    for (j = 1; j <= N; ++j) {
        if (j % 2 == 1) {
            for (i = 2; i <= N - 3; i += 2) {
                int res = query(j, i, j, i + 2);
                g[j][i].push_back({j, i + 2, res});
                g[j][i+2].push_back({j, i, res});
            }
        } else {
            for (i = 1; i <= N - 2; i += 2) {
                int res = query(j, i, j, i + 2);
                g[j][i].push_back({j, i + 2, res});
                g[j][i + 2].push_back({j, i, res});
            }
        }
    }

    for (i = 1; i <= N - 1; ++i) {
        if (i % 2 == 1) {
            int res = query(i, 2, i + 1, 3);
            g[i][2].push_back({i + 1, 3, res});
            g[i + 1][3].push_back({i, 2, res});
        } else {
            int res = query(i, 1, i + 1, 2);
            g[i][1].push_back({i + 1, 2, res});
            g[i + 1][2].push_back({i, 1, res});
        }
    }


    a[1][2] = 0;
    dfs(1, 2);

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            curr.emplace_back(i, j);
            dfs2(i, j, 0);
            curr.pop_back();
        }
    }

    auto res = query(good[0].first, good[0].second, good[3].first, good[3].second);
    if ((a[good[0].first][good[0].second] ^ a[good[3].first][good[3].second]) == res) {
        ivt = 1;
    }

    cout << "!" << endl;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if ((i + j) & 1) {
                cout << (a[i][j] ^ ivt);
            } else {
                cout << a[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}