#include <bits/stdc++.h>
using namespace std;



int main() {
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
      int n;
      scanf("%d", &n);
      if (n % 7 == 0) {
          printf("%d\n", n);
      } else {
          n = n / 10 * 10;
          for (int i = 0 ; i < 10; ++i) {
              if ((n + i) % 7 == 0) {
                  printf("%d\n", n + i);
                  break;
              }
          }
      }
  }
  return 0;
}
