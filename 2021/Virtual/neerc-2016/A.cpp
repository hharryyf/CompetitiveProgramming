/*
   Not my code, Ali coded it on contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   string s;
   while(getline(cin , s)){
      int n = s.length();
      string ans = "";
      vector <string> words;
      for(int i = 0 ; i < n ; i++){
         string cur = "";
         while(i < n && s[i] != '.' && s[i] != ',' && s[i] != ' '){
            cur += s[i];
            i++;
         }
         bool bad = false;
         for(int j = 1 ; j < cur.length() ; j++){
            if(cur[j] < 'a' || cur[j] > 'z'){
               bad = true;
            }
         }
         if(cur.length() < 2 || cur[0] < 'A' || cur[0] > 'Z' || bad){
            if(words.size() > 1){
               for(string s : words){
                  ans += s[0];
               }
               ans += " (";
               int cnt = 0;
               for(string s : words){
                  ans += s;
                  if(cnt != words.size() - 1){
                     ans += " ";
                  }
                  cnt++;
               }
               ans += ") ";
            }
            else if(words.size()){
               ans += words[0];
               ans += " ";
            }
            words.clear();
            ans += cur;
         }
         else{
            words.push_back(cur);
         }
         if(i >= n || s[i] == '.' || s[i] == ',' || cur.length() == 0){
            if(words.size() > 1){
               for(string s : words){
                  ans += s[0];
               }
               ans += " (";
               int cnt = 0;
               for(string s : words){
                  ans += s;
                  if(cnt != words.size() - 1){
                     ans += " ";
                  }
                  cnt++;
               }
               ans += ")";
            }
            else if(words.size()){
               ans += words[0];
            }
            words.clear();
            if(i < n){
               ans += s[i];
               i++;
            }
         }
         if(i < n && s[i] == ' ' && words.empty()){
            ans += s[i];
         }
         else if(s[i] != ' '){
            i--;
         }
      }
      cout << ans << "\n";
   }
}

int32_t main(){
   freopen("abbreviation.in" , "r" , stdin);
   freopen("abbreviation.out" , "w" , stdout);
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
