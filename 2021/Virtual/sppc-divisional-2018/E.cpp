#include <bits/stdc++.h>
#define MAX_SIZE 21
using namespace std;

struct problem {
    char name[55];
    int a, b, c;
    bool operator < (problem other) const {
        if (a + b + c != other.a + other.b + other.c) {
            return (a + b + c) < (other.a + other.b + other.c);
        }
        return a < other.a;
    } 
};

problem a[MAX_SIZE];
int N;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        scanf("%s%d%d%d", a[i].name, &a[i].a, &a[i].b, &a[i].c);
    }

    sort(a, a + N);

    printf("%s\n", a[0].name);
    return 0;
}