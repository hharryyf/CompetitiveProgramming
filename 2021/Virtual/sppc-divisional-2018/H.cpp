#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE];
int N, target = 0;
map<int, int> s;
int tol = 0;
void add(int v) {
    if (s[v] == 0) {
        tol++;
    }
    s[v]++;
}

void del(int v) {
    if (s[v] == 1) {
        tol--;
    }
    s[v]--;
}

int main() {
    int i, j, ans = 1;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%d", &a[i]);
        s[a[i]] = 0;
    }

    target = (int) s.size();

    for (i = 0, j = 0 ; i < N; ++i) {
        while (j <= N && tol < target) {
            add(a[j++]);
        }

        if (tol == target) ans = max(ans, j - i);
        if (tol < target) {
            ans = max(ans, N - i + 2);
        }
        del(a[i]);
    }

    printf("%d\n", ans);
    return 0;
}