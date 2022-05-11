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
   int n;
   cin >> n;
   int cnt[n];
   memset(cnt , 0 , sizeof(cnt));
   for(int i = 0 ; i < n ; i++){
      int x;
      cin >> x;
      x--;
      cnt[x]++;
   }
   int mn = mod;
   int mark[n + 1];
   memset(mark , 0 , sizeof(mark));
   for(int i = 0 ; i < n ; i++){
      if(cnt[i]){
         mn = min(mn , cnt[i]);
      }
      mark[cnt[i]]++;
   }
   vector <int> tp;
   for(int i = 1 ; i <= n ; i++){
      if(mark[i]){
         tp.push_back(i);
      }
   }
   int ret = mod;
   for(int i = mn + 1 ; i > 0 ; i--){
      bool bad = false;
      int ans = 0;
      for(int x : tp){
         if(x % i == 0 || x / i + x % i >= i - 1){
            ans += (x / i + ((x % i) > 0)) * mark[x];
         }
         else{
            bad = true;
         }
      }
      if(!bad){
         ret = min(ret , ans);
      }
   }
   cout << ret << "\n";
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   cin >> t;
   int cur = 1;
   while(t--){
      // cout << "Case #" << cur++ << ": ";
      solve();
   }
   return 0;
}
