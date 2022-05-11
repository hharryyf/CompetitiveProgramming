/*
   Not my code, Ali coded it in contest
*/


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

int par[N];

int pr(int x){
   if(par[x] == x){
      return x;
   }
   return par[x] = pr(par[x]);
}

void solve(){
   int n , m , ka , kb;
   cin >> n >> m >> ka >> kb;
   int app[n + m];
   memset(app , 0 , sizeof(app));
   int a[ka];
   for(int i = 0 ; i < ka ; i++){
      cin >> a[i];
      a[i]--;
      app[a[i]]++;
   }
   int b[kb];
   for(int i = 0 ; i < kb ; i++){
      cin >> b[i];
      b[i]--;
      app[b[i]]++;
   }
   for(int i = 0 ; i < n + m ; i++){
      par[i] = i;
   }
   set <int> l1 , l2;
   for(int i = 0 ; i < n ; i++){
      if(!app[i]){
         l1.insert(i);
      }
   }
   for(int i = n ; i < n + m ; i++){
      if(!app[i]){
         l2.insert(i);
      }
   }
   int ptr1 = 0 , ptr2 = 0;
   vector <pii> ans;
   while(ptr1 < ka || ptr2 < kb){
      if(ptr2 < kb && !l1.empty()){
         int l = *l1.begin();
         l1.erase(l1.begin());
         ans.push_back({b[ptr2] , l});
         app[b[ptr2]]--;
         if(app[b[ptr2]] == 0){
            l2.insert(b[ptr2]);
         }
         par[pr(l)] = pr(b[ptr2++]);
      }
      else if(ptr1 < ka && !l2.empty()){
         int l = *l2.begin();
         l2.erase(l2.begin());
         ans.push_back({a[ptr1] , l});
         app[a[ptr1]]--;
         if(app[a[ptr1]] == 0){
            l1.insert(a[ptr1]);
         }
         par[pr(l)] = pr(a[ptr1++]);
      }
      else{
         cout << "No";
         return;
      }
   }
   if(l1.empty() || l2.empty()){
      cout << "No";
      return;
   }
   for(int x : l1){
      ans.push_back({*l2.begin() , x});
   }
   for(int x : l2){
      if(x == *l2.begin()){
         continue;
      }
      ans.push_back({*l1.begin() , x});
   }
   cout << "Yes\n";
   for(pii x : ans){
      cout << x.first + 1 << " " << x.second + 1 << "\n";
   }
}

int32_t main(){
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
