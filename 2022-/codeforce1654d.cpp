#include <bits/stdc++.h>
#define MAX_SIZE 200119
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;
typedef long long ll;


const ll mod = 998244353;
vector<pair<int, int>> fac[MAX_SIZE];
vector<pair<int, pair<int, int>>> g[MAX_SIZE];
map<int, int> cnt;
int visited[MAX_SIZE];
int N;

inline ll mul(ll x,ll y){
    return x*y%mod;
}

inline ll fastpower(ll x,ll n){
    ll ret=1ll;
    while(n){
        if(n&1)ret=mul(ret,x);
        x=mul(x,x);
        n>>=1;
    }
    return ret;
}

void init() {
    int i, j;
    for (i = 2; i <= 200000; ++i) {
        if (!visited[i]) {
            for (j = 1; j * i <= 200000; ++j) {
                visited[i * j] = 1;
                fac[i * j].emplace_back(i, 0);
            }
        }
    }

    for (i = 2; i <= 200000; ++i) {
        int v = i;
        for (j = 0 ; j < (int) fac[i].size(); ++j) {
            while (v % fac[i][j].first == 0) {
                fac[i][j].second += 1;
                v /= fac[i][j].first;
            }
        }
    }
}

void dfs(int v, map<int, int> &prime, int pre) {
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv == pre) continue;
        int num = np.second.first, den = np.second.second;
        for (auto f : fac[num]) {
            cnt[f.first] -= f.second;
        }

        for (auto f : fac[den]) {
            cnt[f.first] += f.second;
            prime[f.first] = max(prime[f.first], cnt[f.first]);
        }

        dfs(nv, prime, v);

        for (auto f : fac[num]) {
            cnt[f.first] += f.second;
        }

        for (auto f : fac[den]) {
            cnt[f.first] -= f.second;
        }
    }
}

void dfs2(int v, ll curr, ll &tol, int pre) {
    tol += curr;
    debug("id=%d, val=%lld\n", v, curr);
    tol %= mod;
    for (auto np : g[v]) {
        int nv = np.first;
        if (nv == pre) continue;
        int num = np.second.first, den = np.second.second;
        dfs2(nv, (curr * (1ll * num * fastpower(den, mod - 2) % mod)) % mod, tol, v);
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int i, j, x, y;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) g[i].clear();
        cnt.clear();
        map<int, int> prime;
        for (int k = 0 ; k < N - 1; ++k) {
            scanf("%d%d%d%d", &i, &j, &x, &y);
            int gg = __gcd(x, y);
            x /= gg;
            y /= gg;
            g[i].emplace_back(j, make_pair(y, x));
            g[j].emplace_back(i, make_pair(x, y));
        }
        dfs(1, prime, 0);
        ll ans = 1;
        for (auto iter : prime) {
            ans = ans * fastpower(iter.first, iter.second);
            ans %= mod;
        }

        ll tol = 0;
        dfs2(1, ans, tol, 0);
        printf("%lld\n", tol);
    }
    return 0;
}