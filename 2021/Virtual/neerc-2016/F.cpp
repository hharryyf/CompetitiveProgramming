/*
   Not my code, Ali coded it in contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   string s;
   cin >> s;
   s += "@";
   int n = s.length();
   reverse(s.begin() , s.end());
   ld dp[n + 1] , ps[n + 1];
   dp[0] = ps[0] = 0;
   int cnt = 0;
   ll sc = 0 , sw = 0;
   for(int i = 1 ; i < n ; i++){
      cnt += (s[i] == 'C');
      if(s[i] == 'C'){
         sc += i;
      }
      else{
         sw += i;
      }
      dp[i] = ps[i - 1] / i;
      if(s[i] == 'C'){
         dp[i] += (ld)sw / i;
      }
      else{
         dp[i] += (ld)sc / i;
      }
      ps[i] = ps[i - 1] + dp[i];
   }
   cout << fixed << setprecision(9) << dp[n - 1];
}

int32_t main(){
   freopen("foreign.in" , "r" , stdin);
   freopen("foreign.out" , "w" , stdout);
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   // cin >> t;
   int cur = 1;
   while(t--){
      // cout << "Case #" << cur++ << ": ";
      solve();
   }
   return 0;
}
