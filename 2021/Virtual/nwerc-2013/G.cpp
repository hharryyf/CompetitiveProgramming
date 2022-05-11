#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        int g = __gcd(a * b, c - b);
        printf("%d/%d\n", a * b / g, (c - b) / g);
    }
    return 0;
}