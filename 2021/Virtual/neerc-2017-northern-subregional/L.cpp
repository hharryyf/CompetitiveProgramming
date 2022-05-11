#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;
#define FILEIO

void openfile(string filename="little") {
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
}
set<ll> st;
ll N;

bool check(ll d) {
    ll K = N;
    if (d == 1) return false;
    //cout << (K % d) << endl;
    if ((K % d) != 0) return false;
    while (K % d == 0) {
        K = K / d;
    }    

    while (K % (d + 1) == 0) K /= (d + 1);
    return K == 1;
}

void build(ll d) {
    //printf("build %lld\n", d);
    vector<ll> ret;
    ll K = N;
    while (K % d == 0) {
        K = K / d;
        ret.push_back(d);
    }    

    while (K % (d + 1) == 0) {
        K /= (d + 1);
        ret.push_back(d + 1);
    }
    printf("%d", (int) ret.size());
    for (auto v : ret) {
        printf(" %lld", v);
    }
    printf("\n");
}

int main() {
    #ifdef FILEIO
    openfile();
    #endif
    scanf("%lld", &N);
    ll ret = 1;
    while (ret < N) ret = ret * 2;
    if (ret == N) {
        printf("-1\n");
        return 0;
    }

    for (int i = 2; i <= 1000000; ++i) {
        //cout << "check " << i << endl;
        if (check(i)) {
            st.insert(i);
        }
        //cout << "finish " << i << endl;
    }

    if (check(sqrt(N))) {
        st.insert(sqrt(N));
    }

    if (st.find(N) == st.end()) st.insert(N);
    printf("%d\n", (int) st.size());
    for (auto v : st) {
        build(v);
    }
    return 0;
}